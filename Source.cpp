#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Character {
private:
	string name;
	int hp;
	int shield;
	bool isStunned;

public:
	Character(string username, unsigned int health, unsigned int armor) {
		name = username;
		hp = health;
		shield = armor;
	}

	void attack(Character target, Weapon strike) {
		if (!isStunned)
			strike.hit(target);
		else
			cout << name << " is stunned!" << endl;
	}

	unsigned int getHealth() {
		return hp;
	}

	string getName() {
		return name;
	}

	unsigned int getShield() {
		return shield;
	}

	void modifyHealth(int num) {
		hp += num;
	}

	void modifyShield(int num) {
		shield += num;
	}

	void stun() {
		isStunned = true;
	}
};

class Weapon {
private:
	string name;
	unsigned int baseDamage;
	unsigned int accuracy;
	unsigned int critChance;
	float critMult;

public:
	Weapon(string weaponName, unsigned int damage, unsigned int crit) {
		name = weaponName;
		baseDamage = damage;
		if (crit > 100)
			critChance = 100;
		else
			critChance = crit;
	}

	void hit(Character target) {
		if (accuracy > rand() % 100) {//Determine if attack hits target
			bool crit = critChance > rand() % 100;
			unsigned int attackDamage = crit ? baseDamage : (unsigned int)(baseDamage * abs(critMult));//Determine base damage
			if (crit)
				cout << "Critical hit!";
			if (attackDamage > target.getShield()) {//Determine if shield is empty or attack would make shield empty
				attackDamage -= target.getShield();//Subtract shield amount from remaining damage
				target.modifyShield(-target.getShield());//Remove shield
				cout << target.getName() << "'s shield is depleted!" << endl;
				target.modifyHealth(-attackDamage);//Remove health by amount of remaining damage
			}
			else
				target.modifyShield(-attackDamage);
		}
		else
			cout << "Miss!" << endl;
	}
};

void setDifficulty(int level) {
	
}

void viewDifficulty(int level) {
	switch (level) {
	case 5:
		cout << "Realistic: Starting Health = XX, " << endl;
		cout << "Main Weapon = Fists (base damage = XXX and shield health = XXX), Secondary Weapon = (base damage = XXX)" << endl;
		cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
		break;
	case 4:
		cout << "Insane: Starting Health = XXX, " << endl;
		cout << "Main Weapon = base damage = XXX and shield health = XXX), Secondary Weapon = Light Bow(base damage = XXX)" << endl;
		cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
		break;
	case 3:
		cout << "Hard: Starting Health = XXX, " << endl;
		cout << "Main Weapon = Battle Axe(base damage = XXX and shield health = XXX) Secondary Weapon = Long Bow(base damage = XXX), " << endl;
		cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
		break;
	case 2:
		cout << "Normal: Starting Health = XXX, " << endl;
		cout << "Main Weapon = Sword and Shield (base damage = XXX and shield health = XXX), Secondary Weapon = Light Bow(base damage = XXX), " << endl;
		cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
		break;
	default:
		cout << "Easy: Starting health = XXX, " << endl;
		cout << "Main Weapon = Legendary Sword and Shield (base damage = XXX and shield health = XXX), Secondary Weapon = Long Bow(base damage = XXX), " << endl;
		cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
		break;
	}
}

int main() {
	int x = 0;

	cout << "Hello and Welcome to ... " << endl;
	cout << "Within this game you will be set against a random opponent based off the type of challenge you want" << endl;
	cout << "There are multiple different difficulties, ranging from easy to 'impossible' mode" << endl;
	system("pause");
	cout << "Easy will involve a monster with a few attacks and your player having a higher health than normal, and more healing items as well" << endl;
	cout << "Whike on the other hand impossible will have a monster with many different high damaging attacks and your player ";
	cout << "starting with little to no healing items, and a lower starting health as well" << endl;
	system("pause");

	while (x < 1 || x > 5) {
		cout << "Select your difficulty level:" << endl;
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "4. Insane" << endl;
		cout << "5. Realistic" << endl;
		cin >> x;

		viewDifficulty(x);

		string diff;
		switch (x) {
		case 1:
			diff = "easy";
			break;
		case 2:
			diff = "normal";
			break;
		case 3:
			diff = "hard";
			break;
		case 4:
			diff = "insane";
			break;
		case 5:
			diff = "realistic";
			break;
		}
		while (!(x == 'Y' || x == 'y'))
			cout << "Are you ready to play in " << diff << " mode? [Y/N]" << endl;
		
		//THIS NEEDS TO BE CHECKED AND PROBABLY EDITED TO MAKE SURE IT WORKS, AND THEN FILLED IN TO ACTUALLY SET THE DETAILS OF THE DIFFICULTY
		//LIKE CREATING THE CHARACTERS AND GIVING THEM THE WEAPONS AND ALL THAT
	}
	
}
