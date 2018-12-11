#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

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
			unsigned int attackDamage = crit ? baseDamage : baseDamage * abs(critMult);//Determine base damage
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

class Character {
private:
	string name;
	unsigned int hp;
	unsigned int shield;
	bool isStunned;

public:
	Character(string username, unsigned int health, unsigned int armor) {
		name = username;
		hp = health;
		shield = armor;
	}
	
	void attack(Character target, Weapon strike) {
		if(!isStunned)
			strike.hit(target);
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

int main() {
	
}