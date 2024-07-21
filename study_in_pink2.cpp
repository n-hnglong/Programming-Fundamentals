#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

int Check(int &value, int value_max){
    value = value + 0.999;
    if (value > value_max) return value_max;
    else return value;
}

bool Moving(int hp, int exp){
    return (hp > 0 && exp > 0);
}
MapElement::MapElement(ElementType in_type){
    type = in_type;
}

int ManhattanDis(Position p1, Position p2){
    if(p2.isEqual(-1, -1)) return 0;
    return abs(p1.getRow() - p2.getRow()) + abs(p1.getCol() - p2.getCol());
}

Position findNextPos(Position sherlock_pos, Position watson_pos, bool isRobot, Position &pos, Map * map, MovingObject * mv_obj){
    Position direction[4] = {Position(-1, 0), Position(0, -1), Position(1, 0), Position(0, 1)};
    Position move[4];
    if (isRobot == false){
        int largest = INT_MIN;
        for(int i = 0; i < 4; i++) move[i] = pos + direction[i];
        pos = Position::npos;
        for(int i = 0; i < 4; i++) {
            if(ManhattanDis(move[i], sherlock_pos) + ManhattanDis(move[i], watson_pos) > largest && map->isValid(move[i], mv_obj)){
                largest = ManhattanDis(move[i], sherlock_pos) + ManhattanDis(move[i], watson_pos);
                pos = move[i];
            }
        }
        return pos;
    }
    else{
        int nearest = INT_MAX;
        Position temp = direction[1];
        direction[1] = direction[3];
        direction[3] = temp;
        for(int i = 0; i < 4; i++) move[i] = pos + direction[i];
        pos = Position::npos;
        for(int i = 0; i < 4; i++) {
            if(ManhattanDis(move[i], sherlock_pos) + ManhattanDis(move[i], watson_pos) < nearest && map->isValid(move[i], mv_obj)){
                nearest = ManhattanDis(move[i], sherlock_pos) + ManhattanDis(move[i], watson_pos);
                pos = move[i];
            }
        }
        return pos;
    }
}

MapElement::~MapElement(){

}

ElementType MapElement::getType() const{
    return type;
}

int FakeWall::getReqExp() const
{
    return req_exp;
}

Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls) : num_rows(num_rows), num_cols(num_cols){
    map = new MapElement** [num_rows];
    for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement* [num_cols];
        for (int j = 0; j < num_cols; j++){
            map[i][j] = new Path();
        }
    }
    for (int i = 0; i < num_walls; i++){
        int r = array_walls[i].getRow(), c = array_walls[i].getCol();
        delete map[r][c];
        map[r][c] = new Wall();
    }
    for (int i = 0; i < num_fake_walls; i++){
        int r = array_fake_walls[i].getRow(), c = array_fake_walls[i].getCol();
        delete map[r][c];
        map[r][c] = new FakeWall((r * 257 + c * 139 + 89) % 900 + 1);
    }
}

Map::~Map(){
    for (int i = 0; i < num_rows; i++) delete[] map[i];
    delete[] map;
    map = NULL;
}

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    int r = pos.getRow(), c = pos.getCol();
    FakeWall* fakeWall = NULL;
    if (r >= num_rows || c >= num_cols || r < 0 || c < 0) return false;
    ElementType type = map[r][c]->getType();
    switch(type){
        case WALL:
            return false;
        case FAKE_WALL:
            fakeWall = dynamic_cast<FakeWall*>(map[r][c]);
            if (Watson* watson = dynamic_cast<Watson*>(mv_obj)) {
                if (watson->getExp() <= fakeWall->getReqExp()) return false;
                }
        default:
            return true;
    }
}

Position::Position(int r, int c){
    setRow(r);
    setCol(c);
}

Position::Position(const string & str_pos){
    stringstream ss(str_pos);
    char oddChar;
    ss >> oddChar >> r >> oddChar >> c >> oddChar;
}

string Position::str() const{
    return "(" + to_string(r) + "," + to_string(c) + ")";
}

bool Position::isEqual(int in_r, int in_c) const{
    return (in_r == r && in_c == c);
}

bool Position::isEqual(Position pos) const{
    return (pos.getRow() == r && pos.getCol() == c);
}

MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name){
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}

MovingObject::~MovingObject(){

}

const Position Position::npos = Position(-1, -1);

Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(init_hp, init_exp, 0), MovingObject(index, init_pos, map, "Sherlock"){
    this->moving_rule =  moving_rule;
}

Position Sherlock::getNextPosition(){
    Position goto_pos = this->getCurrentPosition();
    int step = this->getStep();
    switch(moving_rule[step]){
        case 'L':
            goto_pos = goto_pos + Position(0, -1);
            break;
        case 'U':
            goto_pos = goto_pos + Position(-1, 0);
            break;
        case 'R':
            goto_pos = goto_pos + Position(0, 1);
            break;
        default:
            goto_pos = goto_pos + Position(1, 0);
            break;
    }
    step = (step + 1) % moving_rule.length();
    this->setStep(step);
    if (map->isValid(goto_pos, this) == false) return Position::npos;
    return goto_pos;
}

void Sherlock::move(){
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(-1,-1) && Moving(this->getHp(), this->getExp())) this->setPos(next_pos);
}

string Sherlock::str() const{
    return name + "[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) : Character(init_hp, init_exp, 0), MovingObject(index, init_pos, map, "Watson"){
    this->moving_rule =  moving_rule;
}

Position Watson::getNextPosition(){
    Position goto_pos = this->getCurrentPosition();
    int step = this->getStep();
    switch(moving_rule[step]){
        case 'L':
            goto_pos = goto_pos + Position(0, -1);
            break;
        case 'U':
            goto_pos = goto_pos + Position(-1, 0);
            break;
        case 'R':
            goto_pos = goto_pos + Position(0, 1);
            break;
        default:
            goto_pos = goto_pos + Position(1, 0);
            break;
    }
    step = (step + 1) % moving_rule.length();
    this->setStep(step);
    if (map->isValid(goto_pos, this) == false) return Position::npos;
    return goto_pos;
}

void Watson::move(){
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(-1,-1) && Moving(this->getHp(), this->getExp())) this->setPos(next_pos);
}

string Watson::str() const{
    return name + "[index=" + to_string(index) + ";pos=" + pos.str() + ";moving_rule=" + moving_rule + "]";
}

Criminal::Criminal(int index, const Position & init_pos, Map *map, Sherlock * sherlock, Watson * watson) : Character(0), MovingObject(index, pos, map, "Criminal"){
    this->sherlock = sherlock;
    this->watson = watson;
    pos = init_pos;
}

Position Criminal::getNextPosition(){
    Position goto_pos = getCurrentPosition();
    return findNextPos(sherlock->getCurrentPosition(), watson->getCurrentPosition(), false, goto_pos, map, this);  
}

void Criminal::move(){
    Position next_pos = getNextPosition();
    int step = this->getStep();
    if(!next_pos.isEqual(-1, -1)) {
        pre_pos = pos;
        pos = next_pos;
        this->setStep(++step);
    }
}

string Criminal::str() const{
    return name + "[index=" + to_string(index) + ";pos=" + pos.str() + "]";
}

ArrayMovingObject::ArrayMovingObject(int capacity) {
    this->capacity = capacity;
    count = 0;
    arr_mv_objs = new MovingObject* [capacity];
}

ArrayMovingObject::~ArrayMovingObject(){
         delete[] arr_mv_objs;
         arr_mv_objs = NULL;
}


bool ArrayMovingObject::isFull() const{
    return count == capacity;
}

bool ArrayMovingObject::add(MovingObject * mv_obj){
    if(isFull() == false) {
        arr_mv_objs[count++] = mv_obj;
        return true;
    }
    return false;
}

string ArrayMovingObject::str() const{
    string str_mv_obj = "";
    for (int i = 0; i < count; i++) {
        str_mv_obj = str_mv_obj + arr_mv_objs[i]->str();
        if (i != (count - 1)) str_mv_obj = str_mv_obj + ";";
    }
    return "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";" + str_mv_obj + "]";
}

int ArrayMovingObject::size() const{
    return count;
}

void subPosition(Position * kind_of_position, string value, int &num){
    int i1 = 0, i2;
    int i = 0;
    while((i1 = value.find('(', i1)) != string::npos){
        i2 = value.find(')', i1);
        if(i2 != string::npos){
            kind_of_position[i] = Position(value.substr(i1, i2 - i1 + 1));
            i++;
            i1 = i2 + 1;
            num = i;
        }
    }
}

Configuration::Configuration(const string & filepath){
    ifstream input_file(filepath);
    string line;
    while (getline(input_file, line)){
        string variable, value;
        variable = line.substr(0,line.find('='));
        value = line.substr(line.find('=') + 1, line.length() - variable.length() - 1);
        if (variable == "MAP_NUM_ROWS") map_num_rows = stoi(value);
        else if (variable == "MAP_NUM_COLS") map_num_cols = stoi(value);
        else if (variable == "MAX_NUM_MOVING_OBJECTS") max_num_moving_objects = stoi(value);
        else if (variable == "SHERLOCK_INIT_HP") sherlock_init_hp = stoi(value);
        else if (variable == "SHERLOCK_INIT_EXP") sherlock_init_exp = stoi(value);
        else if (variable == "WATSON_INIT_HP") watson_init_hp = stoi(value);
        else if (variable == "WATSON_INIT_EXP") watson_init_exp = stoi(value);
        else if (variable == "NUM_STEPS") num_steps = stoi(value);
        else if (variable == "SHERLOCK_INIT_POS") sherlock_init_pos = Position(value);
        else if (variable == "WATSON_INIT_POS") watson_init_pos = Position(value);
        else if (variable == "CRIMINAL_INIT_POS") criminal_init_pos = Position(value);
        else if (variable == "SHERLOCK_MOVING_RULE") sherlock_moving_rule = value;
        else if (variable == "WATSON_MOVING_RULE") watson_moving_rule = value;
        else if (variable == "ARRAY_WALLS") {
            int count = 0;
            for (int i = 0; i < value.length(); i++){
                if(value[i] == '(') count++;
            }
            arr_walls = new Position[count];
            subPosition(arr_walls, value, num_walls);
            str_arr_walls = value;
        }
        else if (variable == "ARRAY_FAKE_WALLS") {
            int count = 0;
            for (int i = 0; i < value.length(); i++){
                if(value[i] == '(') count++;
            }
            arr_fake_walls = new Position[count];
            subPosition(arr_fake_walls, value, num_fake_walls);
            str_arr_fake_walls = value;
        }
        else break;      
    }
    
    input_file.close();
}

Configuration::~Configuration(){
    
    delete[] arr_fake_walls;
    delete[] arr_walls;
    arr_walls = NULL;
    arr_fake_walls = NULL;
}

string Configuration::str() const{
    string str = "Configuration[\n";
    str = str + "MAP_NUM_ROWS=" + to_string(map_num_rows) + '\n'
              + "MAP_NUM_COLS=" + to_string(map_num_cols) + '\n'
              + "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + '\n'
              + "NUM_WALLS=" + to_string(num_walls) + '\n'
              + "ARRAY_WALLS=" + str_arr_walls + '\n'
              + "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + '\n'
              + "ARRAY_FAKE_WALLS=" + str_arr_fake_walls + '\n'
              + "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + '\n'
              + "SHERLOCK_INIT_POS=" + sherlock_init_pos.str() + '\n'
              + "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + '\n'
              + "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + '\n'
              + "WATSON_MOVING_RULE=" + watson_moving_rule + '\n'
              + "WATSON_INIT_POS=" + watson_init_pos.str() + '\n'
              + "WATSON_INIT_HP=" + to_string(watson_init_hp) + '\n'
              + "WATSON_INIT_EXP=" + to_string(watson_init_exp) + '\n'
              + "CRIMINAL_INIT_POS=" + criminal_init_pos.str() + '\n'
              + "NUM_STEPS=" + to_string(num_steps) + '\n' + "]";
    return str;
}

Robot::Robot(RobotType in_type) : MovingObject(index, pos, map, ""){
    robot_type = in_type;
}

Robot::~Robot(){
    
}

RobotType Robot::getType() const{
    return robot_type;
}

RobotC::RobotC(int index, const Position & init_pos, Map * map, Criminal * criminal) : MovingObject(index, pos, map, "RobotC"), Robot(C){
    this->criminal = criminal;
    this->pos = init_pos;
}

Position RobotC::getNextPosition() {
    return criminal->getPre_pos();
}

void RobotC::move(){
    pos = getNextPosition();
}

int RobotC::getDistance(MovingObject *mv_obj) const {
    Position mv_obj_pos = mv_obj->getCurrentPosition();
    return ManhattanDis(pos, mv_obj_pos);
}

string RobotC::str() const {
    return "Robot[pos=" + pos.str() + ";type=C;dist=]";
}

RobotS::RobotS(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock * sherlock) : MovingObject(index, pos, map, "RobotS"), Robot(S){
    this->criminal = criminal;
    this->sherlock = sherlock;
    this->pos = init_pos;
}

Position RobotS::getNextPosition() {
    Position goto_pos = getCurrentPosition();
    return findNextPos(sherlock->getCurrentPosition(), Position::npos, true, goto_pos, map, this);
}

void RobotS::move(){
    Position next_pos = getNextPosition();
    if(!next_pos.isEqual(-1, -1)) {
        pos = next_pos;
    }
}

int RobotS::getDistance() const{
    return ManhattanDis(pos, sherlock->getCurrentPosition());
}

string RobotS::str() const {
    return "Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) + "]";
}

RobotW::RobotW(int index, const Position & init_pos, Map * map, Criminal * criminal, Watson * watson) : MovingObject(index, pos, map, "RobotW"), Robot(W){
    this->criminal = criminal;
    this->watson = watson;
    this->pos = init_pos;
}

Position RobotW::getNextPosition() {
    Position goto_pos = getCurrentPosition();
    return findNextPos(Position::npos, watson->getCurrentPosition(), true, goto_pos, map, this);
}

void RobotW::move(){
    Position next_pos = getNextPosition();
    if(!next_pos.isEqual(-1, -1)) {
        pos = next_pos;
    }
}

int RobotW::getDistance() const{
    return ManhattanDis(pos, watson->getCurrentPosition());
}

string RobotW::str() const {
    return "Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(getDistance()) + "]";

}

RobotSW::RobotSW(int index, const Position & init_pos, Map * map, Criminal * criminal, Sherlock * sherlock, Watson * watson) : MovingObject(index, pos, map, "RobotSW"), Robot(SW){
    this->criminal = criminal;
    this->sherlock = sherlock;
    this->watson = watson;
    this->pos = init_pos;
}

Position RobotSW::getNextPosition() {
    Position goto_pos = getCurrentPosition();
    Position direction[8] = {Position(-2, 0), Position(-1, 1), Position(0, 2), Position(1, 1), Position(2, 0), Position(1, -1), Position(0, -2), Position(-1, -1)};
    Position move[8];
    int nearest = INT_MAX;
    for(int i = 0; i < 8; i++) move[i] = goto_pos + direction[i];
    goto_pos = Position::npos;
    for(int i = 0; i < 8; i++) {
        if(ManhattanDis(move[i], sherlock->getCurrentPosition()) + ManhattanDis(move[i], watson->getCurrentPosition()) < nearest && map->isValid(move[i], this)){
                nearest = ManhattanDis(move[i], sherlock->getCurrentPosition()) + ManhattanDis(move[i], watson->getCurrentPosition());
                goto_pos = move[i];
        }
    }
    return goto_pos;
}

void RobotSW::move(){
    Position next_pos = getNextPosition();
    if(!next_pos.isEqual(-1, -1)) {
        pos = next_pos;
    }
}

int RobotSW::getDistance() const {
    return ManhattanDis(pos, sherlock->getCurrentPosition()) + ManhattanDis(pos, watson->getCurrentPosition());
}

string RobotSW::str() const {
    return "Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(getDistance()) + "]";
}

BaseItem::BaseItem(ItemType in_type){
    type = in_type;
}

BaseItem::~BaseItem(){

}

ItemType BaseItem::getType() const{
    return type;
}
Character::Character(int hp, int exp, int step) : MovingObject(index, pos, map, name){
    this->hp = hp;
    this->exp = exp;
    this->step = step;
}

bool MagicBook::canUse(Character * character, Robot * robot) {
    int exp = character->getExp();
    character->setExp(Check(exp, 900));
    return (character->getExp() <= 350);
}

void MagicBook::use(Character * character, Robot * robot) {
    int exp = character->getExp() * 1.25;
    Check(exp, 900);
    character->setExp(exp);
}

bool EnergyDrink::canUse(Character * character, Robot * robot) {
    int hp = character->getHp();
    character->setHp(Check(hp, 500));
    return (character->getHp() <= 100);
}

void EnergyDrink::use(Character * character, Robot * robot) {
    int hp = character->getHp() * 1.2;
    Check(hp, 500);
    character->setHp(hp);
}

bool FirstAid::canUse(Character * character, Robot * robot) {
    int exp = character->getExp();
    int hp = character->getHp();
    character->setExp(Check(exp, 900));
    character->setHp(Check(hp, 500));
    return ((character->getExp() <= 350 || character->getHp() <= 100));
}

void FirstAid::use(Character * character, Robot * robot) {
    int hp = character->getHp() * 1.5;
    Check(hp, 500);
    character->setHp(hp);
}

bool ExcemptionCard::canUse(Character * character, Robot * robot) {
    return (character->getName() == "Sherlock" && character->getHp() % 2 != 0);
}

void ExcemptionCard::use(Character * character, Robot * robot) {
    character->pass_anyway = true;
}

bool PassingCard::canUse(Character * character, Robot * robot) {
    return (character->getName() == "Watson" && character->getHp() % 2 == 0);
}

void PassingCard::use(Character * character, Robot * robot) {
    if (robot->getName() == this->getChallenge() || this->getChallenge() == "all") character->pass_anyway = true;
    else {
        int exp = character->getExp() - 50;
        Check(exp, 900);
        character->setExp(exp);
        character->pass_anyway = true;
    }
}

int findRobot(int num){
    int n = 0;
    while (num > 0){
        n = n + num % 10;
        num = num / 10;
    }
    return n;
}

void Robot::createItem(Robot * robot){
    Position pos = robot->getCurrentPosition();
    int i = pos.getRow(), j = pos.getCol();
    int p = i * j;
    while (p >= 10) p = findRobot(p);
    if(p == 0 || p == 1) item = new MagicBook();
    else if(p == 2 || p == 3) item = new EnergyDrink();
    else if(p == 4 || p == 5) item = new FirstAid();
    else if(p == 6 || p == 7) item = new ExcemptionCard();
    else {
        int t = (i * 11 + j) % 4;
        switch(t){
        case 0:
            item = new PassingCard("RobotS");
            break;
        case 1:
            item = new PassingCard("RobotW");
            break;
        case 2:
            item = new PassingCard("RobotSW");
            break;
        default:
            item = new PassingCard("all");
            break;
        }
    }
}

bool BaseBag::insert(BaseItem * item){
    if (!isFull()){
        Item * newItem = new Item(item, this->head);
        head = newItem;
        count++;
        return true;
    }
    return false;
}

BaseItem* BaseBag::get(){
    if(head == NULL) return NULL;
    Item * i = head;
    BaseItem * temp = NULL;
    while(i != NULL) {
        if (activeCard == false){
            if(i->value->canUse(obj, NULL) && (i->value->getType() == MAGIC_BOOK || i->value->getType() == ENERGY_DRINK || i->value->getType() == FIRST_AID)){
                temp = i->value;
                i->value = head->value;
                head->value = temp;
                head = head->next;
                count--;
                break;
            }
            i = i->next;
        }
        else {
            if(i->value->canUse(obj, NULL)){
                temp = i->value;
                i->value = head->value;
                head->value = temp;
                head = head->next;
                count--;
                break;
            }
            i = i->next;
        }
    }
    return temp;

}

BaseItem* BaseBag::get(ItemType itemType){
    if(head == NULL) return NULL;
    Item * i = head;
    BaseItem * temp = NULL;
    while (i != NULL){
        if (i->value->getType() == itemType){
            temp = i->value;
            i->value = head->value;
            head->value = temp;
            head = head->next;
            count--;
            break;
        }
        i = i->next;
    }
    return temp;
}

string BaseBag::str() const {
    string str_of_item = "";
    Item * i = head;
    while (i != NULL){
        switch(i->value->getType()){
            case MAGIC_BOOK:
                str_of_item = str_of_item + "MagicBook";
                break;
            case ENERGY_DRINK:
                str_of_item = str_of_item + "EnergyDrink";
                break;
            case FIRST_AID:
                str_of_item = str_of_item + "FirstAid";
                break;
            case EXCEMPTION_CARD:
                str_of_item = str_of_item + "ExcemptionCard";
                break;
            default:
                str_of_item = str_of_item + "PassingCard";
                break;
        }
        if(i->next != NULL) str_of_item = str_of_item + ",";
        i = i->next;
    }
    //if (count == 0) return "Bag[count=0]";
    return "Bag[count=" + to_string(count) + ";" + str_of_item + "]";
}

StudyPinkProgram::StudyPinkProgram(const string & config_file_path){
    
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);

    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);

    sherBag = new SherlockBag(sherlock);
    watBag = new WatsonBag(watson);

}

void StudyPinkProgram::createRobot(int step){
    Position c_pos = criminal->getCurrentPosition();
        if ((step + 1) == 3) robot = new RobotC(3, criminal->getPre_pos(), map, criminal);
        else {
            Position s_pos = sherlock->getCurrentPosition();
            Position w_pos = watson->getCurrentPosition();
            int c_to_s = ManhattanDis(c_pos, s_pos);
            int c_to_w = ManhattanDis(c_pos, w_pos);
            if (c_to_s < c_to_w) robot = new RobotS(arr_mv_objs->count, criminal->getPre_pos(), map, criminal, sherlock);
            else if (c_to_s > c_to_w) robot = new RobotW(arr_mv_objs->count, criminal->getPre_pos(), map, criminal, watson);
            else robot = new RobotSW(arr_mv_objs->count, criminal->getPre_pos(), map, criminal, sherlock, watson);
        }
        robot->createItem(robot);
        arr_mv_objs->add(robot);
}

bool StudyPinkProgram::isStop() const{
    return (sherlock->getHp() <= 1 || watson->getHp() <= 1 || sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()) || watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()));
}

StudyPinkProgram::~StudyPinkProgram(){
    delete config;
    delete map;
    delete criminal;
    delete sherlock;
    delete watson;
    delete sherBag;
    delete watBag;
    delete arr_mv_objs;
}

void StudyPinkProgram::sherlock_vs_robot() {
            switch(robot->getType()){
                case S:
                    if(sherlock->getExp() > 400) sherBag->insert(robot->item);
                    else if(sherlock->pass_anyway == true) break;
                    else {
                        int sherExp = ceil(sherlock->getExp() * 0.9);
                        sherlock->setExp(Check(sherExp, 900));
                    }
                    break;
                case W:
                    sherBag->insert(robot->item);
                    break;
                case SW:
                    if(sherlock->getExp() > 300 && sherlock->getHp() > 335) sherBag->insert(robot->item);
                    else if(sherlock->pass_anyway == true) break;
                    else {
                        int sherExp = ceil(sherlock->getExp() * 0.85);
                        sherlock->setExp(Check(sherExp, 900));
                        int sherHp = ceil(sherlock->getHp() * 0.85);
                        sherlock->setHp(Check(sherHp, 500));
                    }
                    break;
                default:
                    if(sherlock->getExp() <= 500) {
                        sherBag->insert(robot->item);
                        }
                        else sherlock->setPos(criminal->getCurrentPosition());
                    break;

            }
    
    }


void StudyPinkProgram::watson_vs_robot() {
    if (watson->pass_anyway == false) {
            switch(robot->getType()){
                case S:
                    break;
                case W:
                    if(watson->getHp() > 350) watBag->insert(robot->item);
                    else {
                        int watHp = ceil(watson->getHp() * 0.95);
                        watson->setHp(Check(watHp, 500));
                    }
                    break;
                case SW:
                    if(watson->getExp() > 600 && watson->getHp() > 165) watBag->insert(robot->item);
                    else {
                        int watExp = ceil(watson->getExp() * 0.85);
                        watson->setExp(Check(watExp, 900));
                        int watHp = ceil(watson->getHp() * 0.85);
                        watson->setHp(Check(watHp, 500));
                    }
                    break;
                default:
                    watBag->insert(robot->item);
                    break;

            }
    }
    else watBag->insert(robot->item);
}

void StudyPinkProgram::sherlock_watson() {
    if (sherBag->findItem(PASSING_CARD) && watBag->findItem(EXCEMPTION_CARD)){
        BaseItem * sherCard = sherBag->get(PASSING_CARD);
        BaseItem * watCard = watBag->get(EXCEMPTION_CARD);
        while (sherCard != NULL && watCard != NULL) {
            bool t1 = watBag->insert(sherCard);
            bool t2 = sherBag->insert(watCard);
            if(t1 == false && t2 == false) break;
            if(sherBag->findItem(PASSING_CARD) && watBag->findItem(EXCEMPTION_CARD)){
                sherCard = sherBag->get(PASSING_CARD);
                watCard = watBag->get(EXCEMPTION_CARD);        
            }
        }
    }
}

void StudyPinkProgram::before(){
    if(sherlock->getHp() % 2 != 0) {
        BaseItem * sherItem = sherBag->get(EXCEMPTION_CARD);
        if (sherItem != NULL) sherItem->use(sherlock, robot);
        }
    if(watson->getHp() % 2 == 0) {
        BaseItem * watItem = watBag->get(PASSING_CARD);
        if (watItem != NULL) watItem->use(watson, robot);
        }
}

void StudyPinkProgram::after(){

    sherBag->activeCard = false;
    watBag->activeCard = false;
    
    BaseItem * sherItem = sherBag->get();
    BaseItem * watItem = watBag->get();
    
    if (sherItem != NULL) sherItem->use(sherlock, robot);
    if (watItem != NULL) watItem->use(watson, robot);
    
    sherlock->pass_anyway = false;
    watson->pass_anyway = false;

    sherBag->activeCard = true;
    watBag->activeCard = true;

}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

