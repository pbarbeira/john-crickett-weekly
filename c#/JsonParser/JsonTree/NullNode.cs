﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonParser {
    public class NullNode : JsonNode {
        public NullNode(JsonNode parent): base(parent) { }
    }
}
