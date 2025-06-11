# data\_logger ROS2 Package

## Overview

`data_logger` is a ROS2 package designed to capture, process, and save sensor data and robot states for later analysis. The package integrates with RealSense cameras, saves images, logs robot state data, and supports data writing to disk.

Camera is auto launched through data\_logging\_launch.py.

---

## Nodes

###

### 1. `image_saver_node`

* Subscribes to image topics and saves image frames to disk.
* Uses `cv_bridge` for OpenCV image conversion.
* **Status:** Implemented and tested.
* **Known issues:**

  * Compatibility problems with NumPy 2.x causing crashes. Recommend downgrading NumPy to <2 or recompiling affected modules.

### 2. `data_writer_node`

* Writes logged data (images, robot states) to configured storage locations.
* Loads configuration from YAML file.
* **Status:** Implemented and partially tested.
* **Known issues:**

  * Similar NumPy compatibility issues as `image_saver_node`.

### 3. `robot_saver_node`

* Records robot states such as joint states or transforms.
* Currently supports basic state logging.
* **Status:** Implemented but requires more testing with UR5 robot data.

---

## Workflow

1. **Launch the package** via:

   ```bash
   ros2 launch data_logger data_logging_launch.py
   ```
