#include <stdio.h> // For file io.
#include <stdlib.h> // For random number generation.
#include <stdbool.h> // For boolean variable type.
#include <time.h> // To initialize random seed.
#include <math.h> // For sine, cosine, and sqrt functions.

// Returns either -1 or 1.

int returnMove() {
  int arr[] = {-1,1};
  int random = rand() % 2;
  return arr[random];
  
}

// This function returns distance between two coordinates in the xy-plane.
// It is used to calculate fractal dimension using the method in 1.4.

float getDistance(int x, int y, int x_0, int y_0) {
  float d = sqrt(((x-x_0)*(x-x_0))+((y-y_0)*(y-y_0)));
  return d;
  
}

// Main program.

int main() {
  const int max_iter = 1001; // Max number of particles to introduce.
  const int R = 101; // Size of lattice. Note that this must be odd so there's a well-defined center.
  int center = (R - 1)/2; // Gets center of lattice.
  int grid[R][R]; // Square lattice.
  
  // Variables i, j, c are counting variables.
  // The variables x, y, xn, yn are used in the random walk.
  // Variable choice determines whether or not to random walk vertically or horizontally.
  // Variables xr, yr are used to calculate fractal dimension.
  
  int i, j, c, x, y, xn, yn, choice, xr, yr;
 
  int t = 0; // Tally of number of points within a radius.
  FILE *output; // To write clumping grid. This can be commented out.
  FILE *coords; // To write coordinates.
  FILE *dimension; // To get coordinates to calculate fractal dimension.
  FILE *fractaldim; // To output fractal dimension.
  float theta; // Random angle to get x, y in random walk.
        
  float stick; // Float to determine whether or not particle will stick. Is compared to stickiness.
  
  srand(time(0)); // Initialize random seed so same fractal isn't generated each time.
    
  // If you want to specify stickiness, comment the second line and uncomment the first.
    
  // const float stickiness = 0; // Setting stickiness to 0 makes it so that the particle will always stick.
  float stickiness = (float)rand()/(float)(RAND_MAX);
    
  // If you want to set r. Keep first line commented, else, comment out the second and uncomment the first.
  
  // float r = (float)(rand() % center) + 1; // Get a random radius.
  const float r = 30; // This is the radius we use to calculate C(r).
  
  // Initialize the clumping grid.
  
  for (i = 0; i < R; i++) {
    for (j = 0; j < R; j++) {
      grid[i][j] = 0;
      
    }
    
  }
  
  grid[center][center] = 1; // Set mass at center.
  
  // Start particle somewhere.
  
  for (c = 0; c < max_iter; c++) {
    theta = ((float)rand()/(float)(RAND_MAX))*2*M_PI;
    x = center + 0.95*(center - 1)*cos(theta); // Set higher scaling for less clumped fractals.
    y = center + 0.95*(center - 1)*sin(theta);
    
    // Random walk.
    
    for (;;) {
      choice = rand() % 2; // Determines whether to move vertically or horizontally.
      
      if (choice == 0) {
        xn = x + returnMove();
        if (xn > 0 && xn < (R - 1) && grid[xn][y] != 1) x = xn; // Because of stick, we need to check whether or not a particle is already in spot before we can move there.
        
      }
      
      if (choice == 1) {
        yn = y + returnMove();
        if (yn > 0  && yn < (R - 1) && grid[x][yn] != 1) y = yn;
        
      }
      
      bool found = false;
      stick = (float)rand()/(float)(RAND_MAX);
      
      // Check for adjacents.
      
      for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
          if (grid[x + i][y + j] == 1 && stick > stickiness) { // If stick is greater than stickiness, we stick.
            found = true;
            break;
            
          }
          
        }
        
        if (found == true) break;
        
      }
      
      if (found == true) break;
      
    }
    
    grid[x][y] = 1; // Attach particle to mass.
    
  }
  
  output = fopen("output.dat", "w");
  coords = fopen("coords.dat", "w");
  
  // Write clumping grid to output.dat.
  
  for (i = 0; i < R; i++) {
    for (j = 0; j < R; j++) {
      fprintf(output, "%i ", grid[i][j]);
      
    }
    
    fprintf(output, "\n");
    
  }
    
  fclose(output);
  
  // Coordinates of points which are a part of the mass get printed to a file for plotting in matplotlib.
  // See scatter.py for more details on that.
  
  for (i = 0; i < R; i++) {
    for (j = 0; j < R; j++) {
      if (grid[i][j] == 1) {
          fprintf(coords, "%i %i\n", i, j);
        
      } 
    
    }

  }

  fclose(coords);

  // Reads coordinates and calculates distance from each point which is part of the mass. 
  // Increments tally if point is within specified radius.
  // Used to calculate fractal dimension.

  dimension = fopen("coords.dat", "r");
  
  // Read until blank line. I know for a fact there is always a blank line at end of coordinates.dat.
  
  for (;;) {
    int nread = fscanf(dimension, "%i %i", &xr, &yr); // 
    if (!(nread >= 1)) break;
    if (getDistance(xr, yr, center, center) < r) {
      t++;
      
    }
    
  }
  
  fclose(dimension);
  
  // Print fractal dimension to a file.
  // Can be plotted using matplotlib. 
  
  fractaldim = fopen("dimension.dat", "a+");
  
  fprintf(fractaldim, "%i %i %i %i %f\n", (int)r, (int)r, t, (int)(r*r), stickiness); // Print r^D and r to a file to plot. D is always between 1 and 2, as demonstrated. Also print stickiness to investigate correlation between stickiness and fractal dimension.
  fclose(fractaldim);
  
}
