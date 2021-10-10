#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include <fstream>

class Playable //абстрактный класс
{
public:
	int hp; //Параметры персонажа
	int sp;
	int level;
	int attack;
	int exp; //Текучщий опыт
	int expToNext; //Опыт до следующего уровня
	std::string name;

	//Графические переменные
	int x, y; //Позиция игрока
	sf::Sprite PlayableSprite;
	std::string SpritePath;

	void LevelUp() {
		level++;
		hp = hp + level;
		sp = sp + level;
		attack = attack + level * 0.5;
	}

	void ExpGain(int SumOfLevel) { //Функция рассчитывает опыт
		exp += SumOfLevel * 0.5;
		if (exp >= expToNext)
			LevelUp();
		exp = 0;
		expToNext += 20 * level;
	}

	void Draw(sf::RenderWindow& window) {
		window.draw(PlayableSprite);
	}

	void SaveStatus() {
		rapidjson::Value json_val;
		rapidjson::Document doc;
		auto& allocator = doc.GetAllocator();

		doc.SetObject();

		json_val.SetString(name.c_str(), allocator); //Сохраняем json
		doc.AddMember("name", json_val, allocator);

		json_val.SetInt(hp);
		doc.AddMember("hp", json_val, allocator);

		json_val.SetInt(level);
		doc.AddMember("level", json_val, allocator);

		json_val.SetInt(sp);
		doc.AddMember("sp", json_val, allocator);

		json_val.SetInt(attack);
		doc.AddMember("attack", json_val, allocator);

		json_val.SetInt(exp);
		doc.AddMember("exp", json_val, allocator);

		json_val.SetInt(expToNext);
		doc.AddMember("expToNext", json_val, allocator);

		json_val.SetString(SpritePath.c_str(), allocator);
		doc.AddMember("SpritePath", json_val, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		const std::string& str = buffer.GetString();
		std::ofstream json("Characters/" + name + ".json"); //Записываем имя героя и сохраняем
		json << str;
	}

	void LoadStatus() {
		rapidjson::Document doc;
		std::ifstream json("Charcters/" + name + ".json");
		std::string file;
		while (!json.eof()) {
			std::string elementOfJson;
			json >> elementOfJson;
			file += elementOfJson;
		}
		doc.Parse(file.c_str());

		static const char* members[] = { "name", "hp", "level",
										 "sp", "attack", "exp", "expToNext", "SpritePath"};
		for (size_t i = 0; i < sizeof(members) / sizeof(members[0]); i++)
			if (!doc.HasMember(members[i]))
				throw std::runtime_error("missing fields");
		if (name != doc["name"].GetString()) {
			throw std::runtime_error("Invalid File");
		}
		hp = doc["hp"].GetInt();
		level = doc["level"].GetInt();
		sp = doc["sp"].GetInt();
		attack = doc["attack"].GetInt();
		exp = doc["exp"].GetInt();
		expToNext = doc["expToNext"].GetInt();
		SpritePath = doc["SpritePath"].GetString();
	}
};

