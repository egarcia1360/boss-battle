#include <iostream>
#include <string>
using namespace std;

class Weapon {
private:
	string name;
	int baseDamage;
	int accuracy;
	int critChance;
	float critMult;

public:
	Weapon(string weaponName, int damage, int weaponAccuracy, int critProbability, float critMultiplier) {
		name = weaponName;
		baseDamage = damage;
		
		if (weaponAccuracy > 100)
			accuracy = 100;
		else if (weaponAccuracy < 0)
			accuracy = 0;
		else
			accuracy = weaponAccuracy;

		if (critProbability > 100)
			critChance = 100;
		else if (critProbability < 0)
			critChance = 0;
		else
			critChance = critProbability;
	}

	int getAccuracy() {
		return accuracy;
	}

	int getCritChance() {
		return critChance;
	}

	float getCritMult() {
		return critMult;
	}

	int getDamage() {
		return baseDamage;
	}

	string getName() {
		return name;
	}
};

class Character {
private:
	string name;
	int hp;
	int shield;
	unsigned int turnCounter = 0;
	unsigned int recovery = 0;

public:
	Character(string username, int health, int armor) {
		name = username;
		hp = health;
		shield = armor;
	}

	void attack(Character target, Weapon strike) {
		int enemyHealthStart = target.getHealth();
		if (!isStunned()) {
			if (strike.getAccuracy() > rand() % 100) {//Determine if attack hits target
				bool crit = strike.getCritChance() > rand() % 100;
				int baseDamage = strike.getDamage();
				int attackDamage = crit ? baseDamage : (unsigned int)(baseDamage * strike.getCritMult());//Determine base damage
				if (crit) {
					cout << "CRITICAL HIT!";
					cout << target.getName() << " is stunned for the next " << target.turnsToRecover() << " turns!" << endl;
				}
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
				cout << "MISS!" << endl;
		}
		else
			cout << name << " is stunned!" << endl;
		cout << name << " dealt " << (enemyHealthStart - target.getHealth());
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

	int getTurn() {
		return turnCounter;
	}

	bool isStunned() {
		if (recovery > turnCounter)
			return true;
		else
			return false;
	}
	
	void modifyHealth(int num) {
		hp += num;
	}

	void modifyShield(int num) {
		shield += num;
	}

	void nextTurn() {
		turnCounter++;
	}
	
	void stun() {
		unsigned int stunDuration = rand() % 3;
		recovery = turnCounter + stunDuration;
	}

	int turnsToRecover() {
		if (isStunned())
			return recovery - turnCounter;
		else
			return 0;
	}
};

void viewDifficulty(int level) {
	switch (level) {
	case 1:
		cout << "Easy: Starting health = XXX, " << endl;
		break;
	case 2:
		cout << "Normal: Starting Health = XXX, " << endl;
		break;
	case 3:
		cout << "Hard: Starting Health = XXX, " << endl;
		break;
	case 4:
		cout << "Insane: Starting Health = XXX, " << endl;
		break;
	default:
		cout << "Warrior: Starting Health = XX, " << endl;
		break;
	}
}

int main() {
	int x = 0;
	char yeet = '?';
	int difficulty = 0;
	string name;
	bool userYes = false;
	Character player = Character("player_null", 0, 0);
	Character boss = Character("boss_null", 0, 0);

	cout << "Hello and welcome to The Youtube Rewind 2018 of Boss Battles!" << endl;
	cout << "To start off, please enter a name for your character." << endl;
	cin >> name;
	
	do {
		cout << "Select your difficulty level:" << endl;
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "4. Insane" << endl;
		cout << "5. Warrior" << endl;
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
		default:
			diff = "warrior";
			break;
		}
		
		int hp = 0;
		int armor = 0;
		string bosses[] = { "Troll", "Dragon", "Basilisk", "Demon", "Dark Lord" };
		
		if (x > 0 && x < 6) {
			cout << "Ready to play in " << diff << " mode? [Y/N]" << endl;
			cin >> yeet;
			userYes = (yeet == 'Y' || yeet == 'y');
			if (userYes) {
				hp = 250 * (x + 1);
				armor = 250 * (x + 1);
				player = Character(name, hp, armor);
				cout << "[" << name << "]\nHealth: " << hp << "\nArmor: " << armor << endl;
				string bossName = bosses[x - 1];
				int bossHealth = 500 * (x + 1);
				int bossArmor = 1000 * (x + 1);
				boss = Character(bossName, bossHealth, bossArmor);
				cout << "[" << bossName << "]\nHealth: " << bossHealth << "\nArmor: " << bossArmor << endl;
			}
		}
	} while (((x < 1) || (x > 5)) || !userYes);

	string weaponNames[] = { "Greatsword", "Rapier", "Battleaxe", "Shortbow", "Healing Spell" };
	int damageVals[] = { 200, 150, 250, 150, -300 };
	int accuracyVals[] = { 75, 80, 70, 95, 100 };
	int critChanceVals[] = { 10, 15, 5, 20, 0 };
	float critMultVals[] = { 1.5, 1.2, 2.5, 1.1, 1 };
	bool used[] = {false, false, false, false, false};
	
	int invCount = 0;
	Weapon playerLoadout[] = { Weapon("Empty", 0, 0, 0, 0), Weapon("Empty", 0, 0, 0, 0), Weapon("Empty", 0, 0, 0, 0) };
	
	do {
		cout << "Select three of the following weapons." << endl;
		cout << "Inventory: " << invCount << "/3 Slots Filled" << endl;
		for (unsigned int i = 0; i < 5; i++) {
			cout << (i + 1) << ". " << weaponNames[i] << endl;
			cout << "\t" << abs(damageVals[i]) << ((damageVals[i] >= 0) ? " Damage" : " Healing") << endl;
			cout << "\t" << accuracyVals[i] << "% Accuracy" << endl;
			cout << "\t" << critChanceVals[i] << "% Chance of Critical Hit (" << critMultVals[i] << "x Damage)" << endl;
		}
		cin >> x;
		int index = x - 1;
		if (x > 0 && x < 6 && !used[index]) {
			playerLoadout[invCount] = Weapon(weaponNames[index], damageVals[index], accuracyVals[index], critChanceVals[index], critMultVals[index]);
			invCount++;
			used[index] = true;
		}
		else {
			if (x < 1 || x > 5)
				cout << "You may only choose weapons using numbers 1-5." << endl;
			if (used[index])
				cout << "You can only equip one of each weapon type." << endl;
		}
	} while ((x < 1) || (x > 5) || (invCount < 3));

	cout << "LET THE BATTLE BEGIN!" << endl;
	system("pause");
	
	do {
		x = 0;
		player.nextTurn();
		cout << "BEGIN TURN " << player.getTurn() << endl;
		
		while (x < 1 || x > 3) {
			cout << player.getName() << ", choose your move . . ." << endl;
			for (int i = 0; i < 3; i++) {
				cout << (i + 1) << ". " << playerLoadout[i].getName();
				cout << "\t" << abs(playerLoadout[i].getDamage()) << ((playerLoadout[i].getDamage() >= 0) ? " Damage" : " Healing") << endl;
				cout << "\t" << playerLoadout[i].getAccuracy() << "% Accuracy" << endl;
				cout << "\t" << playerLoadout[i].getCritChance() << "% Chance of Critical Hit (" << playerLoadout[i].getCritMult() << "x Damage)" << endl;
			}
			cin >> x;
		}

		player.attack(boss, playerLoadout[x - 1]);

		boss.nextTurn();
		cout << "THE GAME IS GOING" << endl;

		/*
		MISSING:

		BOSS RETALIATION WITH RANDOMIZED ATTACKS
		GAME ENDS WHEN HEALTH REACHES 0

		MISSION FAILED, WE'LL GET 'EM NEXT TIME . . .
		*/
	} while (true);
}
