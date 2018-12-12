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

void easy() {
	char x;

	cout << "Easy: Starting health = XXX, " << endl;
	cout << "Main Weapon = Legendary Sword and Shield (base damage = XXX and shield health = XXX), Secondary Weapon = Long Bow(base damage = XXX), " << endl;
	cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
	cout << "Continue with this mode? Y/N" << endl;
	cin >> x;

	if (x == 'Y' || x == 'y' || x == 'yes') {
		cout << "Starting Easy" << endl;
	}
	else if (x== 'N' || x== 'n'){
		cout << "what do you want to play then?" << endl;
	}
};
void normal() {
	char x;

	cout << "Normal: Starting Health = XXX, " << endl;
	cout << "Main Weapon = Sword and Shield (base damage = XXX and shield health = XXX), Secondary Weapon = Light Bow(base damage = XXX), " << endl;
	cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
	cout << "Continue with this mode? Y/N" << endl;
	cin >> x;

	if (x == 'Y' || x == 'y' || x == 'yes') {
		cout << "Starting Normal" << endl;
	}
	else if (x == 'N' || x == 'n') {
		cout << "what do you want to play then?" << endl;
	}
};
void hard() {
	char x;

	cout << "Hard: Starting Health = XXX, " << endl;
	cout << "Main Weapon = Battle Axe(base damage = XXX and shield health = XXX) Secondary Weapon = Long Bow(base damage = XXX), " << endl;
	cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
	cout << "Continue with this mode? Y/N" << endl;
	cin >> x;

	if (x == 'Y' || x == 'y' || x == 'yes') {
		cout << "Starting Hard" << endl;
	}
	else if (x == 'N' || x == 'n') {
		cout << "what do you want to play then?" << endl;
	}
};
void insane() {
	char x;

	cout << "Insane: Starting Health = XXX, " << endl;
	cout << "Main Weapon = base damage = XXX and shield health = XXX), Secondary Weapon = Light Bow(base damage = XXX)" << endl;
	cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
	cout << "Continue with this mode? Y/N" << endl;
	cin >> x;

	if (x == 'Y' || x == 'y' || x == 'yes') {
		cout << "Starting Insane" << endl;
	}
	else if (x == 'N' || x == 'n') {
		cout << "what do you want to play then?" << endl;
	}
};
void realistic() {
	char x;

	cout << "Realistic: Starting Health = XX, " << endl;
	cout << "Main Weapon = Fists (base damage = XXX and shield health = XXX), Secondary Weapon = (base damage = XXX)" << endl;
	cout << "Healing items = X Large Potions, X Medium Potions, X Maximum Potion (Large heals XXX, Medium heals XXX, Maximum fills health)" << endl;
	cout << "Continue with this mode? Y/N" << endl;
	cin >> x;

	if (x == 'Y' || x == 'y' || x == 'yes') {
		cout << "Starting Realistic" << endl;
	}
	else if (x == 'N' || x == 'n') {
		cout << "what do you want to play then?" << endl;
	}
};

int main() {
	int x;
	int y;

	cout << "Hello and Welcome to ... " << endl;
	cout << "Within this game you will be set against a random opponent based off the type of challenge you want" << endl;
	cout << "There are multiple different difficulties, ranging from easy to 'impossible' mode" << endl;
	system("pause");
	cout << "Easy will involve a monster with a few attacks and your player having a higher health than normal, and more healing items as well" << endl;
	cout << "Whike on the other hand impossible will have a monster with many different high damaging attacks and your player ";
	cout << "starting with little to no healing items, and a lower starting health as well" << endl;
	system("pause");

	cout << "What type of mode would you like to do?" << endl;
	cout << "1. Easy" << endl;
	cout << "2. Normal" << endl;
	cout << "3. Hard" << endl;
	cout << "4. Insane" << endl;
	cout << "5. Realistic" << endl;
	cin >> x;

	if (x == 1) {
		easy();
	}
	else if (x == 2) {
		normal();
	}
	else if (x == 3) {
		hard();
	}
	else if (x == 4) {
		insane();
	}
	else if (x == 5) {
		realistic();
	}
}
