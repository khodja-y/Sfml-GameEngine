// #include <SFML/Window.hpp>
// #include <SFML/OpenGL.hpp>
// #include <SFML/Graphics.hpp>
	
// #include <GL/glut.h>
#include <stdexcept>
#include <iostream>

#include <Book/Game.hpp>
#include <Book/Application.hpp>

// void displayMe(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glBegin(GL_POLYGON);
//         glVertex3f(0.5, 0.0, 0.5);
//         glVertex3f(0.5, 0.0, 0.0);
//         glVertex3f(0.0, 0.5, 0.0);
//         glVertex3f(0.0, 0.0, 0.5);
//     glEnd();
//     glFlush();
// }

int main(){


    try{
        Application game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\Exception : " << e.what() << std::endl;
    }

    return 0;
    
}


// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }

//     return 0;
// }

// int main(int argc, char* argv[])
// {
//     // create the window
//     sf::Window window(sf::VideoMode(800, 600), "OpenGL");
//     //window.setVerticalSyncEnabled(true);

//     // sf::WindowSettings Settings;
//     // Settings.DepthBits         = 24; // Demande un Z-buffer 24 bits
//     // Settings.StencilBits       = 8;  // Demande un stencil-buffer 8 bits
//     // Settings.AntialiasingLevel = 2;  // Demande 2 niveaux d'anti-crénelage
//     // sf::Window window(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close, Settings);

//     // sf::WindowSettings Settings = window.GetSettings();

//     // Initialisation des valeurs d'effacement pour les tampons de couleur et de profondeur
//     glClearDepth(1.f);
//     glClearColor(0.f, 0.f, 0.f, 0.f);

//     // Activation de la lecture et de l'écriture dans le tampon de profondeur
//     glEnable(GL_DEPTH_TEST);
//     glDepthMask(GL_TRUE);

//     // Mise en place d'une projection perspective
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(90.f, 1.f, 1.f, 500.f);

    

//     // load resources, initialize the OpenGL states, ...

//     // run the main loop
//     bool running = true;
//     while (running)
//     {
//         // handle events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 // end the program
//                 running = false;
//             }
//             else if (event.type == sf::Event::Resized)
//             {
//                 // adjust the viewport when the window is resized
//                 glViewport(0, 0, event.size.width, event.size.height);
//             }
//         }

//         // activate the window
//         window.setActive(true);

//         // clear the buffers
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         // draw...

//         glMatrixMode(GL_MODELVIEW);
//         glLoadIdentity();
//         glTranslatef(0.f, 0.f, -200.f);
//         glRotatef(sf::Clock().GetElapsedTime() * 50, 1.f, 0.f, 0.f);
//         glRotatef(sf::Clock().GetElapsedTime() * 30, 0.f, 1.f, 0.f);
//         glRotatef(sf::Clock().GetElapsedTime() * 90, 0.f, 0.f, 1.f);
        

//         glBegin(GL_QUADS);

//             glVertex3f(-50.f, -50.f, -50.f);
//             glVertex3f(-50.f,  50.f, -50.f);
//             glVertex3f( 50.f,  50.f, -50.f);
//             glVertex3f( 50.f, -50.f, -50.f);

//             glVertex3f(-50.f, -50.f, 50.f);
//             glVertex3f(-50.f,  50.f, 50.f);
//             glVertex3f( 50.f,  50.f, 50.f);
//             glVertex3f( 50.f, -50.f, 50.f);

//             glVertex3f(-50.f, -50.f, -50.f);
//             glVertex3f(-50.f,  50.f, -50.f);
//             glVertex3f(-50.f,  50.f,  50.f);
//             glVertex3f(-50.f, -50.f,  50.f);

//             glVertex3f(50.f, -50.f, -50.f);
//             glVertex3f(50.f,  50.f, -50.f);
//             glVertex3f(50.f,  50.f,  50.f);
//             glVertex3f(50.f, -50.f,  50.f);

//             glVertex3f(-50.f, -50.f,  50.f);
//             glVertex3f(-50.f, -50.f, -50.f);
//             glVertex3f( 50.f, -50.f, -50.f);
//             glVertex3f( 50.f, -50.f,  50.f);

//             glVertex3f(-50.f, 50.f,  50.f);
//             glVertex3f(-50.f, 50.f, -50.f);
//             glVertex3f( 50.f, 50.f, -50.f);
//             glVertex3f( 50.f, 50.f,  50.f);

//         glEnd();

        
//         // end the current frame (internally swaps the front and back buffers)
//         //window.draw();
//         //displayMe();
//         window.display();
//     }

//     // release resources...

//     return 0;
// }
