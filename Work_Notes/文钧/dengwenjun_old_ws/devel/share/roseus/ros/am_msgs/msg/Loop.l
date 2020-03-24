;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::Loop)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'Loop (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::LOOP")
  (make-package "AM_MSGS::LOOP"))

(in-package "ROS")
;;//! \htmlinclude Loop.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass am_msgs::Loop
  :super ros::object
  :slots (_header _frontCenter _frontRight _rearLeft _rearRight _A0 _N _F _G1 _G2 _G3 _QA0 _QF _QN ))

(defmethod am_msgs::Loop
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:frontCenter __frontCenter) 0)
    ((:frontRight __frontRight) 0)
    ((:rearLeft __rearLeft) 0)
    ((:rearRight __rearRight) 0)
    ((:A0 __A0) (instance am_msgs::LoopData :init))
    ((:N __N) (instance am_msgs::LoopData :init))
    ((:F __F) (instance am_msgs::LoopData :init))
    ((:G1 __G1) (instance am_msgs::LoopData :init))
    ((:G2 __G2) (instance am_msgs::LoopData :init))
    ((:G3 __G3) (instance am_msgs::LoopData :init))
    ((:QA0 __QA0) (instance am_msgs::LoopData :init))
    ((:QF __QF) (instance am_msgs::LoopData :init))
    ((:QN __QN) (instance am_msgs::LoopData :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _frontCenter (round __frontCenter))
   (setq _frontRight (round __frontRight))
   (setq _rearLeft (round __rearLeft))
   (setq _rearRight (round __rearRight))
   (setq _A0 __A0)
   (setq _N __N)
   (setq _F __F)
   (setq _G1 __G1)
   (setq _G2 __G2)
   (setq _G3 __G3)
   (setq _QA0 __QA0)
   (setq _QF __QF)
   (setq _QN __QN)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:frontCenter
   (&optional __frontCenter)
   (if __frontCenter (setq _frontCenter __frontCenter)) _frontCenter)
  (:frontRight
   (&optional __frontRight)
   (if __frontRight (setq _frontRight __frontRight)) _frontRight)
  (:rearLeft
   (&optional __rearLeft)
   (if __rearLeft (setq _rearLeft __rearLeft)) _rearLeft)
  (:rearRight
   (&optional __rearRight)
   (if __rearRight (setq _rearRight __rearRight)) _rearRight)
  (:A0
   (&rest __A0)
   (if (keywordp (car __A0))
       (send* _A0 __A0)
     (progn
       (if __A0 (setq _A0 (car __A0)))
       _A0)))
  (:N
   (&rest __N)
   (if (keywordp (car __N))
       (send* _N __N)
     (progn
       (if __N (setq _N (car __N)))
       _N)))
  (:F
   (&rest __F)
   (if (keywordp (car __F))
       (send* _F __F)
     (progn
       (if __F (setq _F (car __F)))
       _F)))
  (:G1
   (&rest __G1)
   (if (keywordp (car __G1))
       (send* _G1 __G1)
     (progn
       (if __G1 (setq _G1 (car __G1)))
       _G1)))
  (:G2
   (&rest __G2)
   (if (keywordp (car __G2))
       (send* _G2 __G2)
     (progn
       (if __G2 (setq _G2 (car __G2)))
       _G2)))
  (:G3
   (&rest __G3)
   (if (keywordp (car __G3))
       (send* _G3 __G3)
     (progn
       (if __G3 (setq _G3 (car __G3)))
       _G3)))
  (:QA0
   (&rest __QA0)
   (if (keywordp (car __QA0))
       (send* _QA0 __QA0)
     (progn
       (if __QA0 (setq _QA0 (car __QA0)))
       _QA0)))
  (:QF
   (&rest __QF)
   (if (keywordp (car __QF))
       (send* _QF __QF)
     (progn
       (if __QF (setq _QF (car __QF)))
       _QF)))
  (:QN
   (&rest __QN)
   (if (keywordp (car __QN))
       (send* _QN __QN)
     (progn
       (if __QN (setq _QN (car __QN)))
       _QN)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _frontCenter
    4
    ;; int32 _frontRight
    4
    ;; int32 _rearLeft
    4
    ;; int32 _rearRight
    4
    ;; am_msgs/LoopData _A0
    (send _A0 :serialization-length)
    ;; am_msgs/LoopData _N
    (send _N :serialization-length)
    ;; am_msgs/LoopData _F
    (send _F :serialization-length)
    ;; am_msgs/LoopData _G1
    (send _G1 :serialization-length)
    ;; am_msgs/LoopData _G2
    (send _G2 :serialization-length)
    ;; am_msgs/LoopData _G3
    (send _G3 :serialization-length)
    ;; am_msgs/LoopData _QA0
    (send _QA0 :serialization-length)
    ;; am_msgs/LoopData _QF
    (send _QF :serialization-length)
    ;; am_msgs/LoopData _QN
    (send _QN :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _frontCenter
       (write-long _frontCenter s)
     ;; int32 _frontRight
       (write-long _frontRight s)
     ;; int32 _rearLeft
       (write-long _rearLeft s)
     ;; int32 _rearRight
       (write-long _rearRight s)
     ;; am_msgs/LoopData _A0
       (send _A0 :serialize s)
     ;; am_msgs/LoopData _N
       (send _N :serialize s)
     ;; am_msgs/LoopData _F
       (send _F :serialize s)
     ;; am_msgs/LoopData _G1
       (send _G1 :serialize s)
     ;; am_msgs/LoopData _G2
       (send _G2 :serialize s)
     ;; am_msgs/LoopData _G3
       (send _G3 :serialize s)
     ;; am_msgs/LoopData _QA0
       (send _QA0 :serialize s)
     ;; am_msgs/LoopData _QF
       (send _QF :serialize s)
     ;; am_msgs/LoopData _QN
       (send _QN :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _frontCenter
     (setq _frontCenter (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _frontRight
     (setq _frontRight (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _rearLeft
     (setq _rearLeft (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _rearRight
     (setq _rearRight (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; am_msgs/LoopData _A0
     (send _A0 :deserialize buf ptr-) (incf ptr- (send _A0 :serialization-length))
   ;; am_msgs/LoopData _N
     (send _N :deserialize buf ptr-) (incf ptr- (send _N :serialization-length))
   ;; am_msgs/LoopData _F
     (send _F :deserialize buf ptr-) (incf ptr- (send _F :serialization-length))
   ;; am_msgs/LoopData _G1
     (send _G1 :deserialize buf ptr-) (incf ptr- (send _G1 :serialization-length))
   ;; am_msgs/LoopData _G2
     (send _G2 :deserialize buf ptr-) (incf ptr- (send _G2 :serialization-length))
   ;; am_msgs/LoopData _G3
     (send _G3 :deserialize buf ptr-) (incf ptr- (send _G3 :serialization-length))
   ;; am_msgs/LoopData _QA0
     (send _QA0 :deserialize buf ptr-) (incf ptr- (send _QA0 :serialization-length))
   ;; am_msgs/LoopData _QF
     (send _QF :deserialize buf ptr-) (incf ptr- (send _QF :serialization-length))
   ;; am_msgs/LoopData _QN
     (send _QN :deserialize buf ptr-) (incf ptr- (send _QN :serialization-length))
   ;;
   self)
  )

(setf (get am_msgs::Loop :md5sum-) "92ab15532a8fc5e195e713df1d41a4bf")
(setf (get am_msgs::Loop :datatype-) "am_msgs/Loop")
(setf (get am_msgs::Loop :definition-)
      "Header header
int32 frontCenter
int32 frontRight
int32 rearLeft
int32 rearRight
LoopData A0
LoopData N
LoopData F
LoopData G1
LoopData G2
LoopData G3
LoopData QA0
LoopData QF
LoopData QN 
 
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
MSG: am_msgs/LoopData
int32 frontCenter
int32 frontRight
int32 rearLeft
int32 rearRight
 
")



(provide :am_msgs/Loop "92ab15532a8fc5e195e713df1d41a4bf")


