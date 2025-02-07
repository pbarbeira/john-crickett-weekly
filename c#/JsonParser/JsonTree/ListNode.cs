using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonParser
{
    public class ListNode : JsonNode{

        public IList<JsonNode> Elements = new List<JsonNode>();

        public ListNode(JsonNode parent): base(parent) {}

        public void AddElement(JsonNode child) {
            Elements.Add(child);
        }
    }
}
