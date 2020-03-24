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

class CurrentStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.state = null;
      this.subState = null;
      this.mode = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('state')) {
        this.state = initObj.state
      }
      else {
        this.state = 0;
      }
      if (initObj.hasOwnProperty('subState')) {
        this.subState = initObj.subState
      }
      else {
        this.subState = 0;
      }
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CurrentStatus
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [state]
    bufferOffset = _serializer.int16(obj.state, buffer, bufferOffset);
    // Serialize message field [subState]
    bufferOffset = _serializer.int16(obj.subState, buffer, bufferOffset);
    // Serialize message field [mode]
    bufferOffset = _serializer.int16(obj.mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CurrentStatus
    let len;
    let data = new CurrentStatus(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [state]
    data.state = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [subState]
    data.subState = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [mode]
    data.mode = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'am_msgs/CurrentStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3c9ffe94e8f0a9d6014780d8cebb049b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Topic that is meant to reflect contents of command family "CurrentStatus" with command "GetStatusKeepAlive" from Automower TIF
    
    Header header
    
    # -1 = undefined
    # 0 = Power-up state
    # 1 = Waiting state
    # 2 = Irregular cutting state
    # 3 = Searching CS state
    # 4 = Charging state
    # 5 = Leaving CS state
    # 6 = SW downloading state
    # 7 = Fault state. Fatal Error
    # 8 = Fault state. Error
    int16 state
    
    # -1 = undefined
    # 0 = No sub status
    # 1 = Irregular moving
    # 2 = Complex outside
    # 3 = Complex wheels blocked
    # 4 = Complex wheels slipped
    # 5 = Complex outside at reverse
    # 6 = Complex collision
    # 7 = Complex lifted
    # 8 = Local intensive cutting
    # 9 = Follow guide wire 1 in
    # 10 = Follow right boundary wire in
    # 11 = Docking
    # 12 = Fast charging
    # 13 = Top-up charging
    # 14 = Charging ready
    # 15 = Exit angle
    # 16 = Follow guide wire 1 out
    # 17 = Follow right boundary wire out
    # 18 = Complex No Loop Signal
    # 19 = Complex Cutting Means blocked
    # 20 = Complex Cutting Means blocked
    # 21 = Follow guide wire 2 in
    # 22 = Follow guide wire 3 in
    # 23 = Follow guide wire 2 out
    # 24 = Follow guide wire 3 out
    # 25 = Follow left boundary wire in
    # 26 = Follow left boundary wire out
    # 27 = Complex too steep slope
    int16 subState
    
    # -1 = undefined
    # 0 = Power-down mode
    # 1 = Standby mode
    # 2 = Sleep mode
    # 3 = Sub -active mode
    # 4 = Boot mode
    # 5 = Idle mode
    # 6 = Auto mode
    # 7 = Manual mode
    # 8 = Home mode
    int16 mode
    
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
    const resolved = new CurrentStatus(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.state !== undefined) {
      resolved.state = msg.state;
    }
    else {
      resolved.state = 0
    }

    if (msg.subState !== undefined) {
      resolved.subState = msg.subState;
    }
    else {
      resolved.subState = 0
    }

    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    return resolved;
    }
};

module.exports = CurrentStatus;
