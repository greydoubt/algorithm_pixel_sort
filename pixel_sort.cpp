#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    if (argc != 2) {
        cerr << "Usage: ./pixelsort <image_file>" << endl;
        return 1;
    }

    // Load input image
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cerr << "Error: Could not load image " << argv[1] << endl;
        return 1;
    }

    // Define parameters for pixel sorting
    int channel = 0; // Use the first color channel (BGR order)
    bool sort_rows = true; // Sort rows instead of columns
    int start_row = 100; // Only sort rows starting from row 100
    int end_row = 200; // Only sort rows up to row 200

    // Extract rows to be sorted
    Mat rows_to_sort = image(Range(start_row, end_row + 1), Range::all());

    // Convert rows to grayscale
    Mat gray_rows;
    cvtColor(rows_to_sort, gray_rows, COLOR_BGR2GRAY);

    // Apply pixel sorting to grayscale rows
    Mat sorted_rows;
    sortIdx(gray_rows.reshape(1, 0), sorted_rows, SORT_EVERY_ROW + SORT_ASCENDING);

    // Create output image with sorted rows
    Mat sorted_image = image.clone();
    for (int r = 0; r < sorted_rows.rows; r++) {
        int sorted_row_idx = sorted_rows.at<int>(r, 0);
        Mat sorted_row = rows_to_sort.row(sorted_row_idx).clone();
        sorted_row.copyTo(sorted_image.row(start_row + r));
    }

// Save sorted image
imwrite(argv[1], sorted_image);

return 0;

}