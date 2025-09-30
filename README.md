# Computer Vision Homework

Ajou University · Fall 2025  
Instructor: [교수님 성함 (선택)]  
Student: Kim Minchae

This repository contains assignments for the **Computer Vision** course, implemented using **C++** and **OpenCV**.

---

## 📁 Assignment List

| No. | Title                         | Description                        |
|-----|-------------------------------|------------------------------------|
| HW1 | Multiband Blending            | Image blending using Laplacian and Gaussian pyramids |
| HW2 | SIFT Feature Matching         | Detecting and matching keypoints between images |
| HW3 | Object Tracking               | Real-time tracking of moving objects using OpenCV |
| HW4 | Stereo Vision & Depth Estimation | Computing disparity maps from stereo images |

---

## ✅ HW1: Multiband Blending

**Goal:**  
Blend two images (apple and orange) seamlessly using **multi-resolution pyramids** (Laplacian & Gaussian), based on the method proposed by Burt and Adelson.

**Techniques used:**
- Laplacian pyramid decomposition of input images
- Gaussian pyramid decomposition of masks
- Element-wise blending at each pyramid level
- Reconstructing the final blended image

**Steps:**

1. Read input images:
   - `burt_apple.png`
   - `burt_orange.png`
   - `burt_mask.png`

2. Convert all images to `CV_32F` and normalize to [0, 1] range

3. Create `mask_orange` as: mask_orange = Scalar(1,1,1) - mask_apple

4. Construct pyramids:
- Laplacian pyramids for apple and orange
- Gaussian pyramids for mask_apple and mask_orange

5. At each level `i`, blend as: blended[i] = L_apple[i] * G_apple[i] + L_orange[i] * G_orange[i]

6. Reconstruct final image from the blended Laplacian pyramid

7. Save the result as `output_blend.png`

**Result Preview:**

<p align="center">
<img src="HW1_Multiband_Blending/output.png" width="400"/>
</p>

> Result shows smooth transition between apple and orange using mask-based multiband blending

---

## 🔧 Requirements

- C++17 or later
- OpenCV 4.x
- Xcode (on macOS) or CMake (for CLI build)

---

## 🚀 Build Instructions (CMake alternative)

If you want to build using CMake (optional):

```bash
cd HW1_Multiband_Blending
mkdir build && cd build
cmake ..
make
./hw1
