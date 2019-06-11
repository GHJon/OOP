
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <iostream>
#include <sstream>
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    int numSides;
    const double pi= 3.1415927;

    Point m(300,200); // Starting point 

    while (numSides >= 3){
        cout << "Enter number of sides (3 or more): ";
        cin >> numSides;

        if (numSides < 3) break;

        string text = "-sided Polygon";
        string titleText = (static_cast<ostringstream*>(&(ostringstream() << numSides) )->str()) + text;

        Simple_window win(tl,600,400,titleText.c_str()); // make a simple window

        Graph_lib::Polygon *poly = new Graph_lib::Polygon(); // make a shape (a polygon)

        vector<Text*> num; // Vector to hold numbers

        Text *ct = new Text(Point(300,200),"x"); // Center of Text
        num.push_back(ct);

        for (int i = 0; i < numSides; i++){
            int radius = 100;
            double xCor = m.x + radius * cos(-i * 2*pi / numSides + pi/2); // Logic for X-Coordinate
            double yCor = m.y - radius * sin(i * 2*pi / numSides + pi/2); // Logic for Y-Coordinate

            poly->add(Point(xCor, yCor)); // Add Points

            string counter = static_cast<ostringstream*>(&(ostringstream() << i+1))->str(); // Counter to include numbers
            Text *textPoly = new Text(Point(xCor,yCor), counter.c_str());
           
            win.attach(*textPoly); // Attach number to coordinates on polygon
            num.push_back(textPoly);
        }

        poly->set_color(Color::magenta);  // adjust properties of poly

        win.attach(*ct);               // Connect "x" to the center of window
        win.attach (*poly);           // connect poly to the window

        win.wait_for_button();       // give control to the display engine
        win.detach(*poly);          // Take out lines when complete
        for (int j = 0; j < num.size(); j++){ // Delete numbers around polygon
            win.detach(*num[j]);
            delete num[j]; 
            num.erase(num.begin());
        }
        delete poly; // Delete polygon
    }

    return 0;
}
//------------------------------------------------------------------------------
// Change the name of the Window
// Use Dynamic Allocation to change the points on the polygon
// Change the name of the shape (ex. from "Canvas" to "n-sided Polygon")
