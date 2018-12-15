#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Weapon {
private:
	string name;
	int baseDamage;
	int accuracy;
	int critChance;
	float critMult;

public:
	Weapon(string weaponName, int damage, int crit) {
		name = weaponName;
		baseDamage = damage;
		if (crit > 100)
			critChance = 100;
		else
			critChance = crit;
	}

	int getAccuracy() {
		return accuracy;
	}

	int getCritChance() {
		return critChance;
	}

	int getCritMult() {
		return critMult;
	}

	int getDamage() {
		return baseDamage;
	}
};

class Character {
private:
	string name;
	int hp;
	int shield;
	bool isStunned;

public:
	Character(string username, int health, int armor) {
		name = username;
		hp = health;
		shield = armor;
	}

	void attack(Character target, Weapon strike) {
		if (!isStunned) {
			if (strike.getAccuracy() > rand() % 100) {//Determine if attack hits target
				bool crit = strike.getCritChance() > rand() % 100;
				int baseDamage = strike.getDamage();
				int attackDamage = crit ? baseDamage : (unsigned int)(baseDamage * strike.getCritMult());//Determine base damage
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
		else
			cout << name << " is stunned!" << endl;
	}

	int getHealth() {
		return hp;
	}

	string getName() {
		return name;
	}

	int getShield() {
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
	char x = 0;
	char yeet = '?';
	int difficulty = 0;
	string name;

	cout << "Hello and welcome to The Youtube Rewind 2018 of Boss Battles!" << endl;
	cout << "To start off, please name your character." << endl;
	cin >> name;
	
	while ((x < 1) || (x > 5)) {
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
		
		cout << x;

		int hp = 0;
		int armor = 0;
		string bosses[] = { "Troll", "Dragon", "Dark Lord", "Basilisk", "Demon" };
		
		cout << "Ready to play in " << diff << "mode? [Y/N]" << endl;
		cin >> yeet;
		if ((yeet == 'Y') || (yeet = 'y')) {
			hp = 250 * (x + 1);
			armor = 250 * (x + 1);
			Character player = Character(name, hp, armor);
			cout << "[" << name << "]\nHealth: " << hp << "\nArmor: " << armor << endl;
			string bossName = bosses[x - 1];
			int bossHealth = 500 * (x + 1);
			int bossArmor = 1000 * (x + 1);
			Character boss = Character(bossName, bossHealth, bossArmor);
			cout << "[" << bossName << "]\nHealth: " << bossHealth << "\nArmor: " << bossArmor << endl;
			system("pause");
			break;
		}
		system("pause");
		cout << "Wonderful. Now choose 3 weapons." << endl;
		cout << "1. Greatsword" << endl;
		cout << "2. Rapier" << endl;
		cout << "3. Battleaxe" << endl;
		cout << "4. Shortbow" << endl;
		cout << "5. Healing Potion" << endl;
	}
}
