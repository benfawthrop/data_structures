#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);      
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  //
  // IMPLEMENT THIS FUNCTION
  //
  // a small improvement on the NaiveDistanceFieldMethod
  //
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // create a vector to store the positions of black pixels
    std::vector<std::pair<int, int> > black_pixels;
    // loop over the pixels in the input image to find the black pixels
    for (int i = 0; i < w; i++)  {
        for (int j = 0; j < h; j++) {
            const Color& c = input.GetPixel(i,j);
            // check if the pixel is black
            if (c.isBlack()) {
                black_pixels.push_back(std::make_pair(i, j));
            }
        }
    }

    // loops through all the pixels and compares them with the
    // black pixels
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            double closest = -1;
            for (size_t k = 0; k < black_pixels.size(); k++) {
                std::pair<int, int> bp = black_pixels[k];
                // calculate the distance between the two pixels
                double distance = sqrt((i - bp.first) * (i - bp.first)
                        + (j - bp.second) * (j - bp.second));
                // store the closest distance to a black pixel
                if (closest < 0 || distance < closest) {
                    closest = distance;
                }
            }

            assert(closest >= 0);
            answer = std::max(answer, closest);
            // save the data to the distance image
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(closest);
        }
    }
    return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  
  //
  // IMPLEMENT THIS FUNCTION
  //
  // (using the advancing front method, and a priority queue)
  //
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;


    // create a priority queue of pixels
    DistancePixel_PriorityQueue pq;
    // loop over the pixels in the input image to find the black pixels
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            const Color &c = input.GetPixel(i, j);
            DistancePixel* p = &distance_image.GetPixel(i, j);
            // check if the pixel is black
            p->setX(i);
            p->setY(j);
            if (c.isBlack()) {
                p->setValue(0);
                pq.push(p);
                // sets the distance field value to 0 if the pixel is black
            }
        }
    }

    while (!pq.empty()) {
        const DistancePixel* current = pq.top();
        pq.pop();
        double curr_dist = current->getValue();
        // calculates max distance
        answer = std::max(answer, curr_dist);
        int x = current->getX();
        int y = current->getY();
        // makes sure we don't recheck pixels
        input.SetPixel(x, y, Color(0,0,0));
        // collects all neighbor coords into a vector
        std::vector<std::pair<int, int> > neighbors;
        neighbors.push_back(std::make_pair(x - 1, y));
        neighbors.push_back(std::make_pair(x, y + 1));
        neighbors.push_back(std::make_pair(x + 1, y + 1));
        neighbors.push_back(std::make_pair(x - 1, y + 1));
        neighbors.push_back(std::make_pair(x + 1, y));
        neighbors.push_back(std::make_pair(x + 1, y - 1));
        neighbors.push_back(std::make_pair(x, y - 1));
        neighbors.push_back(std::make_pair(x - 1, y - 1));
        for (std::pair<int, int> neighbor : neighbors) {
            // makes sure we are in bounds
            if (neighbor.first < 0 || neighbor.first >= w ||
                neighbor.second < 0 || neighbor.second >= h)
                continue;
            // gets the pixel at the given position
            if (input.GetPixel(neighbor.first, neighbor.second).isBlack()) {
                continue;
            }
            // gets neighbor pixel
            DistancePixel* neighbor_pixel =
                    &distance_image.GetPixel(neighbor.first, neighbor.second);

            // gets the distance between root pixel and the neighbor
            double distance = hypot(neighbor.first - x, neighbor.second - y);
            if (curr_dist + distance < neighbor_pixel->getValue()) {
                // sets value if it is less than it's current value
                neighbor_pixel->setValue(curr_dist + distance);
                if (pq.in_heap(neighbor_pixel)) {
                    // adds to the queue if it doesn't already exist there
                    pq.update_position(neighbor_pixel);
                } else pq.push(neighbor_pixel);
            }
        }
    }
    return answer;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
