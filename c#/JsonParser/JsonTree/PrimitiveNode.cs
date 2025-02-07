using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonParser.JsonTree {
    public class PrimitiveNode<T> : JsonNode {
        public T Value;

        public PrimitiveNode(JsonNode parent): base(parent){}
    }
}
