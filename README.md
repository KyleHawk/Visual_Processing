# Visual_Processing

 ![image](https://user-images.githubusercontent.com/86921341/168400237-e6d83c97-82b9-4919-a9f6-2d9a4041d0cd.png)

Technologies:

C++, Eigen, OpenCV, QT, Visual Studio

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@Please configure Eigen, OpenCV, QT before running the code

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

The functions implemented by this software are:
1. Calculate Projection matrices
2. Calculate the coordinates of the corresponding points of the two pictures
3. Calculate the epipolar line
4. 3D coordinate restoration
5. Data output to file

PS. Another software implements these functions: open two pictures selected by oneself, calculate the basic matrix using the points selected by oneself, and then find the corresponding points and epipolar lines.


This software has several limitations:
1. Two pictures are fixed.
2. The basic matrix of the graph is known
3. The 3D coordinates of the 8 corresponding points are known

Here are the two images we will use:
Click the "open figures" button
 
![image](https://user-images.githubusercontent.com/86921341/168400252-771cbe07-5e93-4a58-9ff4-e540ef9304e4.png)
![image](https://user-images.githubusercontent.com/86921341/168400280-e2705ec6-f84f-4b67-9d39-ba2ecd4dc4d2.png) ![image](https://user-images.githubusercontent.com/86921341/168400293-2c3785ad-5c12-4911-8256-974fddd14229.png)
	

3D coordinates of the four corners OF LEFT PLANE:

 ![image](https://user-images.githubusercontent.com/86921341/168400313-aeba8432-32a3-49d4-b587-548314e7df89.png)

3D coordinates of the four corners OF RIGHT PLANE:

 ![image](https://user-images.githubusercontent.com/86921341/168400339-5d74abdb-ce3e-4a4c-a8a5-c616e427efa2.png)

Fundamental matrix：
 
 ![image](https://user-images.githubusercontent.com/86921341/168400360-a21e35e2-ee21-41d0-b354-343d3b9392e3.png)

 
Features:
1. 

![image](https://user-images.githubusercontent.com/86921341/168400560-65616226-a180-42ff-a991-84f080968c7b.png)


These three buttons will be used to calculate the Projection matrices of the two images, and to calculate the 2D coordinates based on the calculated Projection matrix and 3D coordinates.

This way we get two 2D coordinate arrays. One is real and the other is calculated using the Projection matrix. This way we get the average error.
 
First click on the "Start calculate projection matrixes:" button.
Next, use the mouse to click the four corners on the left in order,
Then click on the four corners on the right.

![image](https://user-images.githubusercontent.com/86921341/168400603-dcd2aae9-3b71-4537-82e4-5de327d8fa38.png)
 
As shown in the figure above, since we first clicked on the 8 corresponding points of image1, then click the "Calculate First projection matrix" button. We will see two files as shown in the image below.
 
![image](https://user-images.githubusercontent.com/86921341/168400615-c13c754c-dc6b-4c95-85ba-443a92633587.png)

![image](https://user-images.githubusercontent.com/86921341/168400620-dea0d152-9b2f-419e-8c7b-ef92eb315319.png)

![image](https://user-images.githubusercontent.com/86921341/168400633-216bc75c-b1e8-452f-98cd-8b0577b9b1e8.png)

 
The steps to compute the matrix and mean error for image2 are the same as for image1.
 
![image](https://user-images.githubusercontent.com/86921341/168400643-67fe2614-23b7-4de3-9701-13dc6d86e2f0.png)


2.	
 
 ![image](https://user-images.githubusercontent.com/86921341/168400648-8015a321-e355-4984-b590-6f817d4c9c0e.png)

This function is used to find the corresponding points on the two graphs and draw the corresponding polar lines.

The function implementation steps to find the corresponding point are:
First find the corresponding epipolar line, and then find the most suitable corresponding point within the limit of the epipolar line.

The following two pictures are, click the point on image1 to find the corresponding point and polar line on image2.

 ![image](https://user-images.githubusercontent.com/86921341/168400668-874202cf-e7f6-49f6-b334-53aad0be9711.png)

![image](https://user-images.githubusercontent.com/86921341/168400684-1a3e4df2-a06e-41e5-82b3-a6902bf5e0ba.png)

 
The following two pictures are, click on the point on image2 to find the corresponding point and polar line on image1.

![image](https://user-images.githubusercontent.com/86921341/168400730-ba51231a-0c7a-4135-a490-33096a61fbb6.png)

![image](https://user-images.githubusercontent.com/86921341/168400816-f4637874-9843-4fc6-b71c-3b43f32d9d9e.png)

 
 
3.
 
This function adds the function of restoring the 3D coordinates of points on the image on the basis of the previous function.
 
 ![image](https://user-images.githubusercontent.com/86921341/168400836-fe9fc530-5d47-4732-bad9-0e09ca06c6cb.png)

![image](https://user-images.githubusercontent.com/86921341/168400843-31cdffe5-3e84-4ff7-abc1-63c30f51ceb5.png)

---------------

![image](https://user-images.githubusercontent.com/86921341/168400862-76ec19b3-6722-401e-84bc-2802a51b926a.png)

![image](https://user-images.githubusercontent.com/86921341/168400875-320ad22b-dd2d-438d-841b-3579d816439e.png)



 
 

