using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonParser
{
    public class ObjectNode : JsonNode{
        public IDictionary<string, JsonNode> Properties = new Dictionary<string, JsonNode>();

        public ObjectNode(JsonNode parent): base(parent) { }

        public bool IsRootNode() {
            return Parent != null;
        }

        public void AddProperty(string propertyName, JsonNode child){
            Properties.Add(propertyName, child);
        }
    }
}
