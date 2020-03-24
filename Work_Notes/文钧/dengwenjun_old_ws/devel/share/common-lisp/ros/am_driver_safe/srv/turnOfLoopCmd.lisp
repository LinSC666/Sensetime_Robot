; Auto-generated. Do not edit!


(cl:in-package am_driver_safe-srv)


;//! \htmlinclude turnOfLoopCmd-request.msg.html

(cl:defclass <turnOfLoopCmd-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass turnOfLoopCmd-request (<turnOfLoopCmd-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <turnOfLoopCmd-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'turnOfLoopCmd-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_driver_safe-srv:<turnOfLoopCmd-request> is deprecated: use am_driver_safe-srv:turnOfLoopCmd-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <turnOfLoopCmd-request>) ostream)
  "Serializes a message object of type '<turnOfLoopCmd-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <turnOfLoopCmd-request>) istream)
  "Deserializes a message object of type '<turnOfLoopCmd-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<turnOfLoopCmd-request>)))
  "Returns string type for a service object of type '<turnOfLoopCmd-request>"
  "am_driver_safe/turnOfLoopCmdRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'turnOfLoopCmd-request)))
  "Returns string type for a service object of type 'turnOfLoopCmd-request"
  "am_driver_safe/turnOfLoopCmdRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<turnOfLoopCmd-request>)))
  "Returns md5sum for a message object of type '<turnOfLoopCmd-request>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'turnOfLoopCmd-request)))
  "Returns md5sum for a message object of type 'turnOfLoopCmd-request"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<turnOfLoopCmd-request>)))
  "Returns full string definition for message of type '<turnOfLoopCmd-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'turnOfLoopCmd-request)))
  "Returns full string definition for message of type 'turnOfLoopCmd-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <turnOfLoopCmd-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <turnOfLoopCmd-request>))
  "Converts a ROS message object to a list"
  (cl:list 'turnOfLoopCmd-request
))
;//! \htmlinclude turnOfLoopCmd-response.msg.html

(cl:defclass <turnOfLoopCmd-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass turnOfLoopCmd-response (<turnOfLoopCmd-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <turnOfLoopCmd-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'turnOfLoopCmd-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_driver_safe-srv:<turnOfLoopCmd-response> is deprecated: use am_driver_safe-srv:turnOfLoopCmd-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <turnOfLoopCmd-response>) ostream)
  "Serializes a message object of type '<turnOfLoopCmd-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <turnOfLoopCmd-response>) istream)
  "Deserializes a message object of type '<turnOfLoopCmd-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<turnOfLoopCmd-response>)))
  "Returns string type for a service object of type '<turnOfLoopCmd-response>"
  "am_driver_safe/turnOfLoopCmdResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'turnOfLoopCmd-response)))
  "Returns string type for a service object of type 'turnOfLoopCmd-response"
  "am_driver_safe/turnOfLoopCmdResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<turnOfLoopCmd-response>)))
  "Returns md5sum for a message object of type '<turnOfLoopCmd-response>"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'turnOfLoopCmd-response)))
  "Returns md5sum for a message object of type 'turnOfLoopCmd-response"
  "d41d8cd98f00b204e9800998ecf8427e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<turnOfLoopCmd-response>)))
  "Returns full string definition for message of type '<turnOfLoopCmd-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'turnOfLoopCmd-response)))
  "Returns full string definition for message of type 'turnOfLoopCmd-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <turnOfLoopCmd-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <turnOfLoopCmd-response>))
  "Converts a ROS message object to a list"
  (cl:list 'turnOfLoopCmd-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'turnOfLoopCmd)))
  'turnOfLoopCmd-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'turnOfLoopCmd)))
  'turnOfLoopCmd-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'turnOfLoopCmd)))
  "Returns string type for a service object of type '<turnOfLoopCmd>"
  "am_driver_safe/turnOfLoopCmd")