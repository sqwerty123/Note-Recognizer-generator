//
//  main.cpp
//  sound
//
//  Created by  Gleb on 12.07.2020.
//  Copyright © 2020  Gleb. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

const int width  = 1600;
const int height = 1200;


void drawSoundLine(){
    
}



int main(int argc, const char * argv[]) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Thick Line", sf::Style::Default, settings);
    
    sf::SoundBuffer buff;
    std::string sound_path = "/Users/gleb/Projects/C++/SFML/sound/sound/Collide.wav";
    if (!buff.loadFromFile(sound_path)){
        std::cout << "\n---ERROR can't load sound---\n\n";
    }
    /*sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();*/
    
    //unsigned long long n = buff.getSampleCount();
    //int r = buff.getSampleRate();
    const short *samples = buff.getSamples();
    //int d = buff.getDuration().asMilliseconds();
    
    int arr[width];
    sf::VertexArray line(sf::Lines, width * 2 - 1);
    for (int i = 0; i < width; i++){
        arr[i] = (int)(samples[i*7] / 20) + height / 2;
        //printf("%d  ", arr[i]);
    }
    for (int i = 0; i < width - 1; i++){
        line[i * 2].position = sf::Vector2f(i, arr[i]);
        line[i * 2 + 1].position = sf::Vector2f(i, arr[i + 1]);
    }
    
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        
        window.clear();
        window.draw(line);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
    return 0;
}
