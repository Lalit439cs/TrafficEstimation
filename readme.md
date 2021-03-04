Run the application using make all and make run.

Enter image and video names in separate lines including their directory and extension.
Example: "C:\Users\User\Desktop\empty.jpg" and "C:\Users\User\Desktop\trafficvideo.mp4"
What not to give: "empty trafficvideo"

Choose 4 points on the road plane in the following order: top left, bottom left, bottom right, top right

A video will start playing showing the pixels considered in white.
Pixels are considered for moving or queue density only if they are not in background.
The output is printed as Frame Number, Moving Density, Queue Density.

out.txt and plot.png is submitted along with the code. This is the recived by using outstream instead of cout and plotting using matplotlib in python.
