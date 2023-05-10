import numpy as np
import cv2
import matplotlib.pyplot as plt
import skimage.feature as feature

#this is the path to the image that will be used for the assignment, change it to the path of the image you want to use
image_path = 'C:\Github Stuff\computer-graphics\Programming Assignment Five\Sample_image.jpg'

def read_image(image_path):
    "reads an image from a file"
    return cv2.imread(image_path)

def color_conversion():
    "converts an image to grayscale and binary with each being displayed in a separate window"
    try:
        #read the image from the same directory as the program
        image = read_image(image_path)
    except:
        print("Image not found")
        return
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    binary_image = cv2.threshold(gray_image, 127, 255, cv2.THRESH_BINARY)[1]
    cv2.imshow("RGB Image", image)
    cv2.imshow("Grayscale Image", gray_image)
    cv2.imshow("Binary Image", binary_image)

def histogram():
    "displays the histogram of an image in each of the three color channels"
    try:
        #read the image from the same directory as the program
        image = read_image(image_path)
    except:
        print("Image not found")
        return
    color = ('b', 'g', 'r')
    #calculate the histogram for each color channel
    for i, col in enumerate(color):
        histogram = cv2.calcHist([image], [i], None, [256], [0, 256])
        plt.plot(histogram, color=col)
        plt.xlim([0, 256])
    plt.show()

def edge_detection():
    "displays the edges of an image in a separate window"
    try:
        #read the image from the same directory as the program
        image = read_image(image_path)
    except:
        print("Image not found")
        return
    #Calculate the edges using the Canny algorithm
    edges = cv2.Canny(image, 100, 200)
    cv2.imshow("Edges", edges)

def texture_analysis():
    "uses glcm to analyze the texture of an image and displays the contrast, correlation, energy, and homogeneity"
    try:
        #read the image from the same directory as the program
        image = read_image(image_path)
    except:
        print("Image not found")
        return
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    graycom = feature.greycomatrix(gray_image, [1], [0, np.pi/4, np.pi/2, 3*np.pi/4], levels=256)

    # Find the GLCM properties
    contrast = feature.greycoprops(graycom, 'contrast')
    dissimilarity = feature.greycoprops(graycom, 'dissimilarity')
    homogeneity = feature.greycoprops(graycom, 'homogeneity')
    energy = feature.greycoprops(graycom, 'energy')
    correlation = feature.greycoprops(graycom, 'correlation')
    asm = feature.greycoprops(graycom, 'ASM')

    # Print the GLCM properties
    print("Contrast: {}".format(contrast))
    print("Dissimilarity: {}".format(dissimilarity))
    print("Homogeneity: {}".format(homogeneity))
    print("Energy: {}".format(energy))
    print("Correlation: {}".format(correlation))
    print("ASM: {}".format(asm))

def main():
    color_conversion()
    histogram()
    edge_detection()
    texture_analysis()
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()