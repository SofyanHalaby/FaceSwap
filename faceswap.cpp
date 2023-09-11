/*
 * Copyright (C) 2023 Sofyan Gaber <sofyanhalaby@gmail.com>
 *
 * This code is for demonstration and educational purposes. It 
 * is a seed for a face-swap application.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <filesystem>

void draw_bounded_face(cv::Mat& image, cv::Mat& face_img, const cv::Rect& dest)
{
    cv::resize(face_img, face_img, dest.size());
    face_img.copyTo(image(dest));
    cv::rectangle(image, dest, cv::Scalar(255, 0, 0), 2);
}



std::vector<cv::Rect> detect_faces(const cv::Mat& image)
{
    // Load the pre-trained Haar cascade for face detection
    cv::CascadeClassifier faceCascade;
    faceCascade.load("haarcascade_frontalface_default.xml");

    // Convert the image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Detect faces
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 5);

    return faces;
}

void swap_faces(cv::Mat& image, const std::vector<cv::Rect>& faces)
{
    if(faces.size() < 2)
    {
        return;
    }
    std::list<cv::Mat> temp_face_images{image(faces.back()).clone()}; 

    for (size_t i = 0; i < faces.size(); i++)
    {
        temp_face_images.push_back(image(faces[i]).clone());

        draw_bounded_face(image, temp_face_images.front(), faces[i]);

        // cv::resize(temp_face_images.front(), temp_face_images.front(), faces[i].size());
        // temp_face_images.front().copyTo(image(faces[i]));
        temp_face_images.pop_front();
    }
}





int main(int argc, char** argv)
{    
    //this can be inhanced by threading, however i won't do this !
    //should assert for existence of directories !
    for (const auto &entry : std::filesystem::directory_iterator("in")) 
    {
        if (entry.is_regular_file())
        {
            cv::Mat image = cv::imread(entry.path().string());
            if (image.empty())
            {
                continue;
            }
            
            auto faces = detect_faces(image);
            swap_faces(image, faces);
            cv::imwrite("out/" + entry.path().filename().string(), image);
        }
    }
}
