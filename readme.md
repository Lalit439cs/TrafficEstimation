# Traffic Density Estimator
• Developed Traffic Density Estimator for Queue & dynamic traffic from traffic video using OpenCV function in C++ <br>

• For this software design ,analysed utility-runtime trade-of using the parameters-sub-sampling frames,splitwork 
across threads,reduce resolution for each frame etc.

## Compiling Instructions
<!-- **Compiling Instructions** <br> -->
Follow below steps to run the code-<br>

Run the application using make all and make run.

Enter empty image and video path names in separate lines including their directory and extension. Example: "C:\Users\User\Desktop\empty.jpg" and "C:\Users\User\Desktop\trafficvideo.mp4" What not to give: "empty trafficvideo"

Choose 4 points on the road plane in the following order: top left, bottom left, bottom right, top right

A video will start playing showing the pixels considered in white. Pixels are considered for moving or queue density only if they are not in background. The output is printed as Frame Number, Moving Density, Queue Density.

out.csv and plot.png is submitted along with the code. This is the received by using outstream instead of cout and plotting using matplotlib in python.
The code used to plot the graph is also submitted as plot.py.

The lines needed to get the file has been commented. Uncomment them to get make the out.txt yourself.
Running the code will only output the required lines in the console as stdout.

## DECLARATION
<!-- **DECLARATION** <br> -->
This project was created collaboratively by Arka Mandal and Lalit Meena during COP290, Software Design Practices course(Spring 2021,Prof.Rijurekha Sen).
