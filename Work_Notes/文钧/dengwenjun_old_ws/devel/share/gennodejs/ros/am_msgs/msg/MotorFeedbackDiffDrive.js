// Auto-generated. Do not edit!

// (in-package am_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let MotorFeedback = require('./MotorFeedback.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class MotorFeedbackDiffDrive {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.left = null;
      this.right = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('left')) {
        this.left = initObj.left
      }
      else {
        this.left = new MotorFeedback();
      }
      if (initObj.hasOwnProperty('right')) {
        this.right = initObj.right
      }
      else {
        this.right = new MotorFeedback();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MotorFeedbackDiffDrive
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [left]
    bufferOffset = MotorFeedback.serialize(obj.left, buffer, bufferOffset);
    // Serialize message field [right]
    bufferOffset = MotorFeedback.serialize(obj.right, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MotorFeedbackDiffDrive
    let len;
    let data = new MotorFeedbackDiffDrive(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [left]
    data.left = MotorFeedback.deserialize(buffer, bufferOffset);
    // Deserialize message field [right]
    data.right = MotorFeedback.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += MotorFeedback.getMessageSize(object.left);
    length += MotorFeedback.getMessageSize(object.right);
    return length;
  }

  static datatype() {
    // Returns string type for a message object
    return 'am_msgs/MotorFeedbackDiffDrive';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '17ed5e1da280dd97ff21ded1ea2d0771';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    MotorFeedback left
    MotorFeedback right
    
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
    
    ================================================================================
    MSG: am_msgs/MotorFeedback
    Header header
    float32 omega
    float32 current
    int32 ticks
    float32 controlOmega
    float32 controlPower
    bool hold_position
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MotorFeedbackDiffDrive(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.left !== undefined) {
      resolved.left = MotorFeedback.Resolve(msg.left)
    }
    else {
      resolved.left = new MotorFeedback()
    }

    if (msg.right !== undefined) {
      resolved.right = MotorFeedback.Resolve(msg.right)
    }
    else {
      resolved.right = new MotorFeedback()
    }

    return resolved;
    }
};

module.exports = MotorFeedbackDiffDrive;
