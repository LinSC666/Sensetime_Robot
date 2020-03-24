;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::DetectionResult)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'DetectionResult (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::DETECTIONRESULT")
  (make-package "AM_MSGS::DETECTIONRESULT"))

(in-package "ROS")
;;//! \htmlinclude DetectionResult.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass am_msgs::DetectionResult
  :super ros::object
  :slots (_header _objects ))

(defmethod am_msgs::DetectionResult
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:objects __objects) (let (r) (dotimes (i 0) (push (instance am_msgs::Object :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _objects __objects)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:objects
   (&rest __objects)
   (if (keywordp (car __objects))
       (send* _objects __objects)
     (progn
       (if __objects (setq _objects (car __objects)))
       _objects)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; am_msgs/Object[] _objects
    (apply #'+ (send-all _objects :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; am_msgs/Object[] _objects
     (write-long (length _objects) s)
     (dolist (elem _objects)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; am_msgs/Object[] _objects
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _objects (let (r) (dotimes (i n) (push (instance am_msgs::Object :init) r)) r))
     (dolist (elem- _objects)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get am_msgs::DetectionResult :md5sum-) "d05414622f3f3b983211d67b7ce383ac")
(setf (get am_msgs::DetectionResult :datatype-) "am_msgs/DetectionResult")
(setf (get am_msgs::DetectionResult :definition-)
      "Header header

Object[] objects

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
MSG: am_msgs/Object
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

")



(provide :am_msgs/DetectionResult "d05414622f3f3b983211d67b7ce383ac")


