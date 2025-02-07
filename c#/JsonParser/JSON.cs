using System.Reflection;
using System.Text.RegularExpressions;
using JsonParser.JsonTree;

namespace JsonParser {
    public class JSON {
        public static T Parse<T>(string jsonString) where T : class {
            if(jsonString == string.Empty) {
                return null;
            }

            if (!jsonString.StartsWith('{')) {
                throw new Exception("Error: missing opening bracket at begin");
            }

            if (!jsonString.EndsWith('}')) {
                throw new Exception("Error: missing closing bracket at end");
            }

            var root = ParseJsonObject(StripStringQuotes(jsonString));

            return ConvertTree<T>(root);
        }

        private static JsonNode ParseJsonObject(string jsonString, JsonNode parent = null) {
            var objRoot = new ObjectNode(parent);
            var tokens = TokenizeJsonString(jsonString);
            foreach(var token in tokens) {
                var kvp = token.Split(':');
                if(kvp.Length != 2 || kvp.ElementAt(1) == string.Empty) {
                    throw new Exception("Invalid formatting");
                }
                var key = kvp.First();
                if (key.First() != '\"') {
                    throw new Exception($"Missing opening quote on key [{key}]");
                }
                if (key.Last() != '\"') {
                    throw new Exception($"Missing closing quote on key [{key}]");
                }
                var value = kvp.Last();
                JsonNode node;
                if (value.First() == '{') {
                    node = ParseJsonObject(StripStringQuotes(value), objRoot);
                    continue;
                }
                if (value.First() == '[') {
                    node = ParseJsonList(StripStringQuotes(value), objRoot);
                    continue;
                }
                node = ParseJsonPrimitive(value, objRoot);
                objRoot.Properties.Add(NormalizeStr(key, true), node);
            }

            return objRoot;
        }

        private static IList<string> TokenizeJsonString(string jsonString) {
            var pattern = @"\""?\w+\""?:(-?\w+([^,\s]+\w+)?|(-?\d+(\.\d+)?|\""?\w+\""?|\{.*\}|\[(\""?\w+(\.\w+)?\""?,\s?|\""?\w+(\.\w+)?\""?)*\]))?";
            return Regex.Matches(jsonString, pattern).Select(x => x.Value).ToList();
        }

        private static JsonNode ParseJsonList(string jsonString, JsonNode parent) {
            var root = new ListNode(parent);
            var tokens = jsonString.Split(',');
            if (tokens[0] != string.Empty) {
                foreach(var token in tokens) {
                    var node = ParseJsonPrimitive(token, root);
                    root.AddElement(node);
                }
            }
            return root;
        }

        private static JsonNode ParseJsonPrimitive(string jsonString, JsonNode parent) {
            if(jsonString.First() != '\"') {
                if(jsonString.Last() == '\"') {
                    throw new Exception($"Invalid format: closing bracket on value [{jsonString}]");
                }
                if(jsonString == "null") {
                    return new NullNode(parent);
                }
                if(jsonString == "true" || jsonString == "false") {
                    return new PrimitiveNode<bool>(parent) {
                        Value = jsonString == "true"
                    };
                }
                return TryParseNumber(jsonString, parent);
            }
            if(jsonString.Last() != '\"') {
                throw new Exception($"Missing closing quote on value [{jsonString.Substring(1)}]");
            }
            return new PrimitiveNode<string>(parent) {
                Value = StripStringQuotes(jsonString)
            };
        }

        private static JsonNode TryParseNumber(string jsonString, JsonNode parent) {
            bool isDouble = false;
            foreach (var c in jsonString) {
                if (c == '.') {
                    if (isDouble) {
                        throw new Exception($"Invalid formatting: two decimal points on  value [{jsonString}]");
                    }
                    isDouble = true;
                }
                if (char.IsLetter(c)) {
                    throw new Exception($"Invalid formatting: cannot parse type on value [{jsonString}]");
                }
            }
            if (isDouble) {
                return new PrimitiveNode<double>(parent) {
                    Value = Convert.ToDouble(jsonString.Replace('.', ','))
                };
            }
            return new PrimitiveNode<int>(parent) {
                Value = Convert.ToInt32(jsonString)
            };
        }

        private static T ConvertTree<T>(JsonNode root) where T: class{
            if(root.GetType() != typeof(ObjectNode)) {
                throw new Exception($"Invalid root subclass. Expected [ObjectNode], got [{root.GetType()}]");
            }
            var properties = (root as ObjectNode).Properties;
            var instance = (T) Activator.CreateInstance(typeof(T));

            var instanceType = instance.GetType();
            foreach(var field in instanceType.GetFields()) {
                if(properties.TryGetValue(field.Name, out var value)) {
                    if(field.FieldType == value.GetType().GetGenericArguments()[0]) {
                        if(value is PrimitiveNode<string> stringNode) {
                            field.SetValue(instance, stringNode.Value);
                            continue;
                        }
                        if (value is PrimitiveNode<int> intNode) {
                            field.SetValue(instance, intNode.Value);
                            continue;
                        }
                        if (value is PrimitiveNode<double> doubleNode) {
                            field.SetValue(instance, doubleNode.Value);
                            continue;
                        }
                        if (value is PrimitiveNode<bool> boolNode) {
                            field.SetValue(instance, boolNode.Value);
                            continue;
                        }
                        continue;
                    }
                    if(value is ListNode listNode) {
                        
                    }
                }
            }
            return instance;
        }

        private static string StripStringQuotes(string str) {
            return str.Substring(1, str.Length - 2);
        }
        
        private static string NormalizeStr(string str, bool stripQuotes = false) {
            str = stripQuotes ? StripStringQuotes(str) : str;
            return char.ToUpper(str[0]) + str.Substring(1);
        }

        public static string Stringify(object obj) {
            return "{}";
        }
    }
}
