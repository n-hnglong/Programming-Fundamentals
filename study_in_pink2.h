/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Robot;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
    
    friend class TestStudyInPink;
};

class Path : public MapElement {
    public:
    Path() : MapElement(PATH){}

    friend class TestStudyInPink;
};

class Wall : public MapElement {
    public:
    Wall() : MapElement(WALL){}

    friend class TestStudyInPink;
};

class FakeWall : public MapElement {
    private:
    int req_exp;
    public:
    FakeWall(int in_req_exp) : MapElement(FAKE_WALL){
            req_exp = in_req_exp;
    }
    int getReqExp() const;

    friend class TestStudyInPink;
};

class Map {
private:
    int num_rows, num_cols;
    MapElement*** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;

    friend class TestStudyInPink;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const{
        return r;
    }
    int getCol() const{
        return c;
    }
    void setRow(int r){
        this->r = r;
    }
    void setCol(int c){
        this->c = c;
    }

    string str() const;

    bool isEqual(int in_r, int in_c) const;

    bool isEqual(Position pos) const;
    
    Position operator+(const Position& pos) const{
        return Position(r + pos.getRow(), c + pos.getCol());
    }

    friend class TestStudyInPink;
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;
    string moving_rule;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name);
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const{
        return pos;
    }
    virtual void move() = 0;
    virtual string str() const = 0;
    int getIndex() const{
        return index;
    }
    friend class TestStudyInPink;
};

class Character : public virtual MovingObject{
    protected:
    int hp, exp, step;
    
    public:
    Character(int step) : MovingObject(index, pos, map, name){
        this->step = step;
    }
    Character(int hp, int exp, int step);
    virtual int getExp() const = 0;
    virtual int getHp() const = 0;

    virtual void setExp(int exp) = 0;
    virtual void setHp(int hp) = 0;

    virtual int getStep() const = 0;
    virtual void setStep(int step) = 0;

    virtual string getName() const = 0;

    bool pass_anyway = false;
    friend class TestStudyInPink;

};

class Sherlock : public Character {
private:
    // TODO
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    // getNextPosition
    Position getNextPosition();
    // move
    void move();
    // str
    string str() const;
    // ...
    int getExp() const override{
        return exp;
    }
    void setExp(int exp) override{
        this->exp = exp;
    }

    void setHp(int hp) override{
        this->hp = hp;
    }
    int getHp() const override{
        return hp;
    }

    int getStep() const override{
        return step;
    }
    void setStep(int step) override{
        this->step = step;
    }
    
    void setPos(Position pos){
        this->pos = pos;
    }
    string getName() const{
        return name;
    }
    friend class TestStudyInPink;
};

class Watson : public Character {
private:
    // TODO
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    // getNextPosition
    Position getNextPosition();
    // move
    void move();
    // str
    string str() const;
    // ...
    int getExp() const override{
        return exp;
    }
    void setExp(int exp) override{
        this->exp = exp;
    }

    void setHp(int hp) override{
        this->hp = hp;
    }
    int getHp() const override{
        return hp;
    }

    int getStep() const override{
        return step;
    }
    void setStep(int step) override{
        this->step = step;
    }

    void setPos(Position pos){
        this->pos = pos;
    }

    string getName() const{
        return name;
    }
    friend class TestStudyInPink;
};

class Criminal : public Character {
private:
    // TODO
    Sherlock * sherlock;
    Watson * watson;
    Position pre_pos;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    // getNextPosition
    Position getNextPosition();
    // move
    void move();
    // str
    string str() const;
    // ...
    int getExp() const override{
        return exp;
    }
    void setExp(int exp) override{
        this->exp = exp;
    }

    void setHp(int hp) override{
        this->hp = hp;
    }
    int getHp() const override{
        return hp;
    }

    int getStep() const override{
        return step;
    }
    void setStep(int step) override{
        this->step = step;
    }

    string getName() const{
        return name;
    }
    Position getPre_pos() const{
        return pre_pos;
    }
    friend class TestStudyInPink;
};

class ArrayMovingObject {
private:
    // TODO
    int count, capacity;
    MovingObject** arr_mv_objs;
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const{
        return arr_mv_objs[index];
    };
    int size() const; // return current number of elements in the array
    string str() const;

    friend class TestStudyInPink;
    friend class StudyPinkProgram;
};

class Configuration {
    friend class TestStudyInPink;
    friend class StudyPinkProgram;
private:
    // TODO
    int map_num_rows, map_num_cols,
        max_num_moving_objects,
        num_walls = 0,
        num_fake_walls = 0,
        sherlock_init_hp,
        sherlock_init_exp,
        watson_init_hp,
        watson_init_exp,
        num_steps;
    Position *arr_walls, *arr_fake_walls;
    Position sherlock_init_pos, watson_init_pos,
             criminal_init_pos;
    string sherlock_moving_rule, watson_moving_rule;
    string str_arr_walls, str_arr_fake_walls;
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...



class Robot : public virtual MovingObject{
    protected:
    RobotType robot_type;
    BaseItem * item;
    
    public:
    Robot(RobotType in_type);
    virtual ~Robot();
    virtual RobotType getType() const;
    void createItem(Robot * robot);

    //bool marked = false;
    virtual string getName() const = 0;
    friend class TestStudyInPink;
    friend class StudyPinkProgram;

};
class BaseItem {
    protected:
    ItemType type;

public:
    BaseItem(ItemType in_type);
    virtual ~BaseItem();
    virtual ItemType getType() const;

    virtual bool canUse(Character* obj, Robot * robot) = 0;
    virtual void use(Character* obj, Robot * robot) = 0;

    friend class TestStudyInPink;
};
class RobotC : public Robot {
    private:
    Criminal * criminal;
    public:
    RobotC(int index, const Position & init_pos, Map * map, Criminal * criminal);
    Position getNextPosition();
    int getDistance(MovingObject * mv_obj) const;
    void move();
    string str() const;

    string getName() const{
        return name;
    }
    friend class TestStudyInPink;
};

class RobotS : public Robot {
    private:
    Criminal * criminal;
    Sherlock * sherlock;
    public:
    RobotS(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock * sherlock);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;

    string getName() const{
        return name;
    }
    
    friend class TestStudyInPink;
};

class RobotW : public Robot {
    private:
    Criminal * criminal;
    Watson * watson;
    public:
    RobotW(int index, const Position & init_pos, Map * map, Criminal * criminal, Watson * watson);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;

    string getName() const{
        return name;
    }
    
    friend class TestStudyInPink;
};

class RobotSW : public Robot {
    private:
    Criminal * criminal;
    Sherlock * sherlock;
    Watson * watson;
    public:
    RobotSW(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock * sherlock, Watson * watson);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;

    string getName() const{
        return name;
    }
    friend class TestStudyInPink;
};



class MagicBook : public BaseItem{
    public:
    MagicBook() : BaseItem(MAGIC_BOOK){}
    bool canUse(Character* obj, Robot * robot) override;
    void use(Character* obj, Robot * robot) override;

    friend class TestStudyInPink;
};

class EnergyDrink : public BaseItem{
    public:
    EnergyDrink() : BaseItem(ENERGY_DRINK){}
    bool canUse(Character* obj, Robot * robot) override; 
    void use(Character* obj, Robot * robot) override;

    friend class TestStudyInPink;

};

class FirstAid : public BaseItem{
    public:
    FirstAid() : BaseItem(FIRST_AID){}
    bool canUse(Character* obj, Robot * robot) override; 
    void use(Character* obj, Robot * robot) override;

    friend class TestStudyInPink;
};

class ExcemptionCard : public BaseItem{
    
    public:
    ExcemptionCard() : BaseItem(EXCEMPTION_CARD){}
    bool canUse(Character* obj, Robot * robot) override; 
    void use(Character* obj, Robot * robot) override;

    friend class TestStudyInPink;
};

class PassingCard : public BaseItem{
    private:
    string challenge;
    
    public:
    PassingCard(string challenge) : BaseItem(PASSING_CARD) {}
    bool canUse(Character* obj, Robot * robot) override; 
    void use(Character* obj, Robot * robot) override;

    string getChallenge() const {
        return challenge;
    }
    void setChallenge(string challenge) {
        this->challenge = challenge;
    }


    friend class TestStudyInPink;
};

class Item{
    public:
    BaseItem * value;
    Item * next;
    Item() : value(NULL), next(NULL){}
    Item(BaseItem * item, Item * next){
        value = item;
        this->next = next;
    }
};

class BaseBag {
    private:
    Character * obj;
    Item * head;
    int count = 0;
    public:
    BaseBag(Character* obj) : head(NULL) {
        this->obj = obj;
    }

    virtual bool insert(BaseItem * item);
    virtual BaseItem * get();
    virtual BaseItem * get(ItemType itemType);
    virtual string str() const;
    virtual bool findItem(ItemType itemType){
        if(head == NULL) return false;
        Item * i = head;
        while (i != NULL) {
            if (i->value->getType() == itemType) return true;
            i = i->next;
        }
        return false;
    }

    virtual bool isFull() const{
        if(obj->getName() == "Sherlock") return count == 13;
        else return count == 15;
    }

    bool activeCard = true;
    int getCount() const {
        return count;
    }
    friend class TestStudyInPink;
};

class SherlockBag : public BaseBag{
    
    public:
    SherlockBag(Sherlock * sherlock) : BaseBag(sherlock) {}

    friend class TestStudyInPink;
};

class WatsonBag : public BaseBag{
    
    public:
    WatsonBag(Watson * watson) : BaseBag(watson) {}


    friend class TestStudyInPink;
};

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    SherlockBag * sherBag;
    WatsonBag * watBag;


    Robot * robot;

    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    ~StudyPinkProgram();

    void createRobot(int step);

    void sherlock_robot(){
        for (int i = 3; i < arr_mv_objs->size(); ++i) {
            if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())) {
                robot = dynamic_cast<Robot*>(arr_mv_objs->get(i));
                before();
                sherlock_vs_robot();
                after();
            }
        }  
    }
    void watson_robot(){
        for (int i = 3; i < arr_mv_objs->size(); ++i) {
            if (watson->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())) {
                robot = dynamic_cast<Robot*>(arr_mv_objs->get(i));
                before();
                watson_vs_robot();
                after();
            }
        } 
    }

    void sherlock_vs_robot();
    void watson_vs_robot();
    void sherlock_watson();
    void before();
    void after();

    bool sherlock_watson_meeting() const {
        return sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition());
    }
    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int i_step = 0; i_step < config->num_steps; ++i_step) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                    if(isStop()) break;
                    if (arr_mv_objs->get(i)->getIndex() == 1){
                        if (sherlock_watson_meeting()){
                            sherlock_watson();
                        }
                        sherlock_robot();
                    }
                    if (arr_mv_objs->get(i)->getIndex() == 2){
                        if (sherlock_watson_meeting()){
                            sherlock_watson();
                        }
                        watson_robot();
                    }
                    if (i == 0 && (i_step + 1) % 3 == 0 ) createRobot(i_step);
                    if (verbose == true) printStep(i_step);
                }
            if(isStop()) {
                printStep(i_step);
                break;
            }
        }
        printResult();
    }

    friend class TestStudyInPink;
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */