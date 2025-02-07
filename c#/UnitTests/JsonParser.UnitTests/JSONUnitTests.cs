using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;

namespace JsonParser.UnitTests {
    [TestClass]
    public class JSONUnitTests{
        private JsonTest ParseString(string jsonString) {
            return JSON.Parse<JsonTest>(jsonString);
        }

        [TestMethod]
        public void Empty_Json_String() {
            var res = ParseString("");
            Assert.IsNull(res);
        }

        [TestMethod]
        public void Valid_Empty_Object() {
            var res = ParseString("{}");
            Assert.IsNotNull(res);
            Assert.IsInstanceOfType<JsonTest>(res);
        }

        [TestMethod]
        public void Missing_Opening_Bracket() {
            Assert.ThrowsException<Exception>(() => ParseString("}"));
        }

        [TestMethod]
        public void Missing_Closing_Bracket() {
            Assert.ThrowsException<Exception>(() => ParseString("{"));
        }

        [TestMethod]
        public void String_Value() {
            var value = "Value";
            var res = ParseString($"{{\"stringKey\":\"{value}\"}}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.StringKey);
            Assert.AreEqual(res.StringKey, value);
        }

        [TestMethod]
        public void Int_Value() {
            var value = 1;
            var res = ParseString($"{{\"intKey\":{value}}}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.IntKey);
            Assert.AreEqual(res.IntKey, value);
        }

        [TestMethod]
        public void Double_Value() {
            var res = ParseString($"{{\"doubleKey\":0.1}}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.DoubleKey);
            Assert.AreEqual(res.DoubleKey, 0.1);
        }

        [TestMethod]
        public void Bool_Value() {
            var res = ParseString($"{{\"boolKey\":true}}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.BoolKey);
            Assert.IsTrue(res.BoolKey);
        }

        [TestMethod]
        public void Invalid_Value() {
            Assert.ThrowsException<Exception>(() => ParseString($"{{\"stringKey\":12abe}}"));
        }

        [TestMethod]
        public void Key_No_Opening_Quote() {
            Assert.ThrowsException<Exception>(() => ParseString("{stringKey:value}"));
        }

        [TestMethod]
        public void Key_No_Closing_Quote() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"stringKey:value}"));
        }

        [TestMethod]
        public void Key_No_Colon() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"stringKey\":value}"));
        }

        [TestMethod]
        public void Key_No_Value() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"stringKey\":}"));
        }

        [TestMethod]
        public void String_Value_No_Opening_Quote() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"stringKey\":value}"));
        }

        [TestMethod]
        public void String_Value_No_Closing_Quote() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"stringKey\":\"value}"));
        }

        [TestMethod]
        public void All_Primitives() {
            var res = ParseString("{\"stringKey\":\"Value\", \"intKey\":1, \"doubleKey\":1.0 \"boolKey\":true}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.StringKey);
            Assert.AreEqual("Value", res.StringKey);
            Assert.IsNotNull(res.IntKey);
            Assert.AreEqual(1, res.IntKey);
            Assert.IsNotNull(res.DoubleKey);
            Assert.AreEqual(1.0, res.DoubleKey);
            Assert.IsNotNull(res.BoolKey);
            Assert.IsTrue(res.BoolKey);
        }

        [TestMethod]
        public void List_No_Elements() {
            var res = ParseString("{\"listKey\":[]}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.ListKey);
            Assert.IsFalse(res.ListKey.Any());
        }

        [TestMethod]
        public void List_One_Element() {
            var res = ParseString("{\"listKey\":[1]}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.ListKey);
            Assert.AreEqual(1, res.ListKey.Count());
        }

        [TestMethod]
        public void List_Multiple_Elements() {
            var res = ParseString("{\"listKey\":[1,2,3,4,5]}");
            Assert.IsNotNull(res);
            Assert.IsNotNull(res.ListKey);
            Assert.AreEqual(5, res.ListKey.Count());
        }

        [TestMethod]
        public void List_Multiple_Elements_Different_Types() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"listKey\":[1,\"wrong\"]}"));
        }

        [TestMethod]
        public void List_Multiple_Elements_Wrong_Type() {
            Assert.ThrowsException<Exception>(() => ParseString("{\"listKey\":[1.0, 2.0]}"));
        }


        private class JsonTest {
            public string StringKey;
            public int IntKey;
            public double DoubleKey;
            public bool BoolKey;
            public IList<int> ListKey = new List<int>();
        
            public JsonTest() { }

            public JsonTest(string stringKey) {
                StringKey = stringKey;
            }
        }

    }
}