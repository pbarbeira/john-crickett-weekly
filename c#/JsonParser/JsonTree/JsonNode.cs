namespace JsonParser {
    public abstract class JsonNode(JsonNode parent) {
        public JsonNode? Parent = parent;
    }
}
