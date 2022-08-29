const mongoose = require("mongoose");

const nodeSchema = mongoose.Schema({
  records: [{ type: mongoose.Schema.Types.ObjectId, ref: "Record" }],
  longitude: Number,
  latitude: Number,
  firstLevel: Number,
});

const Node = mongoose.model("Node", nodeSchema);

exports.Node = Node;
