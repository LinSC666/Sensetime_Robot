// Auto-generated. Do not edit!

// (in-package am_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class StateInput {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.pathSegmentationBlocked = null;
      this.pathDetectionBlocked = null;
      this.turningDirectionLeft = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('pathSegmentationBlocked')) {
        this.pathSegmentationBlocked = initObj.pathSegmentationBlocked
      }
      else {
        this.pathSegmentationBlocked = false;
      }
      if (initObj.hasOwnProperty('pathDetectionBlocked')) {
        this.pathDetectionBlocked = initObj.pathDetectionBlocked
      }
      else {
        this.pathDetectionBlocked = false;
      }
      if (initObj.hasOwnProperty('turningDirectionLeft')) {
        this.turningDirectionLeft = initObj.turningDirectionLeft
      }
      else {
        this.turningDirectionLeft = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type StateInput
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [pathSegmentationBlocked]
    bufferOffset = _serializer.bool(obj.pathSegmentationBlocked, buffer, bufferOffset);
    // Serialize message field [pathDetectionBlocked]
    bufferOffset = _serializer.bool(obj.pathDetectionBlocked, buffer, bufferOffset);
    // Serialize message field [turningDirectionLeft]
    bufferOffset = _serializer.bool(obj.turningDirectionLeft, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type StateInput
    let len;
    let data = new StateInput(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [pathSegmentationBlocked]
    data.pathSegmentationBlocked = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [pathDetectionBlocked]
    data.pathDetectionBlocked = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [turningDirectionLeft]
    data.turningDirectionLeft = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 3;
  }

  static datatype() {
    // Returns string type for a message object
    return 'am_msgs/StateInput';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '66f3e8700901a4c81c50fee4c374e6c7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    bool pathSegmentationBlocked
    bool pathDetectionBlocked
    bool turningDirectionLeft
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new StateInput(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.pathSegmentationBlocked !== undefined) {
      resolved.pathSegmentationBlocked = msg.pathSegmentationBlocked;
    }
    else {
      resolved.pathSegmentationBlocked = false
    }

    if (msg.pathDetectionBlocked !== undefined) {
      resolved.pathDetectionBlocked = msg.pathDetectionBlocked;
    }
    else {
      resolved.pathDetectionBlocked = false
    }

    if (msg.turningDirectionLeft !== undefined) {
      resolved.turningDirectionLeft = msg.turningDirectionLeft;
    }
    else {
      resolved.turningDirectionLeft = false
    }

    return resolved;
    }
};

module.exports = StateInput;
