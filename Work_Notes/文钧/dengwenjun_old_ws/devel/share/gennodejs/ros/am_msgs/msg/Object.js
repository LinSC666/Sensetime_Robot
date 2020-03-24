// Auto-generated. Do not edit!

// (in-package am_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Rect = require('./Rect.js');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Object {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.object_index = null;
      this.confidence = null;
      this.bounding_box_cv = null;
      this.location_bv = null;
      this.label = null;
    }
    else {
      if (initObj.hasOwnProperty('object_index')) {
        this.object_index = initObj.object_index
      }
      else {
        this.object_index = 0;
      }
      if (initObj.hasOwnProperty('confidence')) {
        this.confidence = initObj.confidence
      }
      else {
        this.confidence = 0.0;
      }
      if (initObj.hasOwnProperty('bounding_box_cv')) {
        this.bounding_box_cv = initObj.bounding_box_cv
      }
      else {
        this.bounding_box_cv = new Rect();
      }
      if (initObj.hasOwnProperty('location_bv')) {
        this.location_bv = initObj.location_bv
      }
      else {
        this.location_bv = [];
      }
      if (initObj.hasOwnProperty('label')) {
        this.label = initObj.label
      }
      else {
        this.label = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Object
    // Serialize message field [object_index]
    bufferOffset = _serializer.int32(obj.object_index, buffer, bufferOffset);
    // Serialize message field [confidence]
    bufferOffset = _serializer.float32(obj.confidence, buffer, bufferOffset);
    // Serialize message field [bounding_box_cv]
    bufferOffset = Rect.serialize(obj.bounding_box_cv, buffer, bufferOffset);
    // Serialize message field [location_bv]
    // Serialize the length for message field [location_bv]
    bufferOffset = _serializer.uint32(obj.location_bv.length, buffer, bufferOffset);
    obj.location_bv.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [label]
    bufferOffset = _serializer.uint8(obj.label, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Object
    let len;
    let data = new Object(null);
    // Deserialize message field [object_index]
    data.object_index = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [confidence]
    data.confidence = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [bounding_box_cv]
    data.bounding_box_cv = Rect.deserialize(buffer, bufferOffset);
    // Deserialize message field [location_bv]
    // Deserialize array length for message field [location_bv]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.location_bv = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.location_bv[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [label]
    data.label = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.location_bv.length;
    return length + 29;
  }

  static datatype() {
    // Returns string type for a message object
    return 'am_msgs/Object';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0c9b334f865e3aab40d33e895236278a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 object_index
    float32 confidence # A value between 0.0 and 1.0.
    Rect bounding_box_cv # A bounding box on the camera coordinate.
    geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.
    uint8 label
    uint8 LABEL_UNKNOWN=0
    uint8 LABEL_PEDESTRIAN=1
    uint8 LABEL_CONE=2
    uint8 LABEL_GOLF=3
    uint8 LABEL_SPRINKLER=4
    
    ================================================================================
    MSG: am_msgs/Rect
    float32 x
    float32 y
    float32 width
    float32 height
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Object(null);
    if (msg.object_index !== undefined) {
      resolved.object_index = msg.object_index;
    }
    else {
      resolved.object_index = 0
    }

    if (msg.confidence !== undefined) {
      resolved.confidence = msg.confidence;
    }
    else {
      resolved.confidence = 0.0
    }

    if (msg.bounding_box_cv !== undefined) {
      resolved.bounding_box_cv = Rect.Resolve(msg.bounding_box_cv)
    }
    else {
      resolved.bounding_box_cv = new Rect()
    }

    if (msg.location_bv !== undefined) {
      resolved.location_bv = new Array(msg.location_bv.length);
      for (let i = 0; i < resolved.location_bv.length; ++i) {
        resolved.location_bv[i] = geometry_msgs.msg.Point.Resolve(msg.location_bv[i]);
      }
    }
    else {
      resolved.location_bv = []
    }

    if (msg.label !== undefined) {
      resolved.label = msg.label;
    }
    else {
      resolved.label = 0
    }

    return resolved;
    }
};

// Constants for message
Object.Constants = {
  LABEL_UNKNOWN: 0,
  LABEL_PEDESTRIAN: 1,
  LABEL_CONE: 2,
  LABEL_GOLF: 3,
  LABEL_SPRINKLER: 4,
}

module.exports = Object;
