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


void getSoundLine(sf::SoundBuffer buff, sf::VertexArray *line, int len_x, int len_millisec){
    unsigned long long sn = buff.getSampleCount();
    const short *samples = buff.getSamples();
    int dur = buff.getDuration().asMilliseconds();
    int factor;
    if (len_millisec == -1){
        factor = (int)(sn / len_x);
    } else {
        factor = (int)((float)(len_millisec * sn) / dur / len_x);
    }
    int arr[len_x];
    for (int i = 0; i < len_x; i++){
        arr[i] = (int)(samples[i * factor] / 20) + height / 2;
        printf("%d ", i * factor);
    }
    for (int i = 0; i < len_x - 1; i++){
        (*line)[i * 2].position = sf::Vector2f(i, arr[i]);
        (*line)[i * 2 + 1].position = sf::Vector2f(i, arr[i + 1]);
    }
}


int main(int argc, const char * argv[]) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Thick Line", sf::Style::Default, settings);
    
    sf::SoundBuffer buff;
    std::string sound_path = "/Users/gleb/Projects/C++/SFML/Note-Recognizer-generator/sound/Collide.wav";
    if (!buff.loadFromFile(sound_path)){
        std::cout << "\n---ERROR can't load sound---\n\n";
    }
    /*sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    int rate = buff.getSampleRate();
    const short *samples = buff.getSamples();
    unsigned long long sn = buff.getSampleCount();
    int dur = buff.getDuration().asMilliseconds();*/
    
    sf::VertexArray line(sf::Lines, width * 2 - 1);
    getSoundLine(buff, &line, width, 1000);
    
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
