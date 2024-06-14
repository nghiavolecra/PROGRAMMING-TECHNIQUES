
////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// TODO:
// Chỉnh lại di chuyển của RobotC (gợi ý: thực hiện hàm getPrevPosition cho Criminal)
// Mô tả về các meet thay đổi (đã được confirm 90%)
// File study_in_pink2.h những phần trước "addition" là gốc của đề (không thay đổi)
// Chỉnh tên thuộc tính hp và exp của Sherlock và Watson
// Position có nạp chồng 2 hàm isEqual
// isStop kiểm tra vị trí Sherlock, Watson với Criminal và hp của Sherlock, Watson
// Hàm run chú ý chỉnh từ hàm run() gốc (vị trí gọi printResult và printStep)
// Hàm move của Sherlock và Watson khi exp == 0 sẽ không thực hiện gì
// NOTE:
// chú ý các phần addition nên sửa đổi để tránh đạo code
// nộp Bkel cần xóa đổi lại 2 hàm printResult và printStep gốc, xóa thuộc tính outputFile

#include "study_in_pink2.h"

// CLASS: MapElement
MapElement::MapElement(ElementType in_type)
{
    type = in_type;
}

ElementType MapElement::getType() const
{
    return type;
}
MapElement::~MapElement()
{
    // Destructor logic if necessary
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: FakeWall
FakeWall::FakeWall(int in_req_exp) : MapElement(ElementType::FAKE_WALL)
{
    req_exp = in_req_exp;
}
int FakeWall::getReqExp() const
{
    return req_exp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Position
Position::Position(int r, int c)
{
    this->r = r;
    this->c = c;
}

// Position::Position()
// {
//     this->r = r;
//     this->c = c;
// }
Position::Position(const string &str_pos)
{
    string sub = str_pos.substr(1, str_pos.size() - 2);
    stringstream ss(sub);
    string tmp;
    int i = 0;
    while (getline(ss, tmp, ','))
    {
        if (i == 0)
        {
            r = stoi(tmp);
            i++;
        }
        else
            c = stoi(tmp);
    }
}
bool Position::operator==(const Position &other) const
{
    return (this->r == other.r && this->c == other.c);
}
int Position::getRow() const
{
    return r;
}
int Position::getCol() const
{
    return c;
}
void Position::setRow(int r)
{
    this->r = r;
}
void Position::setCol(int c)
{
    this->c = c;
}
string Position::str() const
{
    string s = '(' + to_string(r) + ',' + to_string(c) + ')';
    return s;
}
bool Position::isEqual(Position pos) const
{
    return (this->r == pos.r && this->c == pos.c);
}
bool Position::isEqual(int in_r, int in_c) const
{
    return (r == in_r && c == in_c);
}
const Position Position::npos = Position(-1, -1);

int manhattanDistance(const Position &pos1, const Position &pos2)
{
    int x = abs(pos1.getRow() - pos2.getRow());
    int y = abs(pos1.getCol() - pos2.getCol());
    return x + y;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: MovingObject

// MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name = "")
// {
//     this->index = index;
//     this->pos = pos;
//     this->map = map;
//     this->name = name;
// }

MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name)
    : index(index), pos(pos), map(map), name(name)
{
    // initialization code (if any)
}

Position MovingObject::getCurrentPosition() const
{
    return pos;
}
void MovingObject::setPosition(Position pos)
{
    this->pos = pos;
}
Map *MovingObject::getMap() const
{
    return map;
}
int MovingObject::getIndex() const
{
    return index;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Character kế thừa class MovingObject
// Character::Character(int index, const Position pos, Map *map, const string &name = "") : MovingObject(index, pos, map, name) {}

Character::Character(int index, const Position pos, Map *map, const string &name)
    : MovingObject(index, pos, map, name)
{
    // additional initialization for Character (if any)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Sherlock kế thừa class Character
// Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "Sherlock")
// {
//     if (init_hp > 500)
//         this->hp = 500;
//     else
//         this->hp = init_hp;
//     if (init_exp > 900)
//         this->exp = 900;
//     else
//         this->exp = init_EXP;

//     this->moving_rule = moving_rule;
// }

Position Sherlock::getNextPosition()
{
    Position newPos = getCurrentPosition();
    if (new_moving_rule[0] == 'U')
    {
        newPos.setRow(newPos.getRow() - 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'D')
    {
        newPos.setRow(newPos.getRow() + 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'L')
    {
        newPos.setCol(newPos.getCol() - 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'R')
    {
        newPos.setCol(newPos.getCol() + 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }

    Position prePos = newPos;

    return newPos;
}
void Sherlock::move()
{
    if (this->getEXP() == 0)
        return;
    if (!(this->getNextPosition() == Position::npos))
    {
        this->setPosition(getNextPosition());
    }

    // moving_rule += moving_rule[0];

    // moving_rule = moving_rule.substr(1);

    new_moving_rule += new_moving_rule[0];
    new_moving_rule = new_moving_rule.substr(1);
}
string Sherlock::str() const
{
    // trả về chuỗi "Sherlock[index=<index>;pos=<pos>;moving_rule=<moving_rule>]"
    string a1 = "[index=" + to_string(getIndex());
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    // string pos = "(" + to_string(init_pos.getRow()) + "," + to_string(init_pos.getCol()) + ")";
    string a2 = ";pos=" + pos;
    string a3 = ";moving_rule=" + moving_rule + "]";
    string result = "Sherlock" + a1 + a2 + a3;
    return result;
}
MovingObjectType Sherlock::getObjectType() const
{
    return SHERLOCK;
}
int Sherlock::getHP() const { return hp; }
int Sherlock::getEXP() const { return exp; }
void Sherlock::setHP(int hp)
{
    if (hp > 500)
        this->hp = 500;
    else
        this->hp = hp;
}
void Sherlock::setEXP(int EXP)
{
    if (EXP > 900)
        this->exp = 900;
    else
        this->exp = exp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Watson kế thừa class Character
// Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "Watson")
// {
//     if (init_hp > 500)
//         this->hp = 500;
//     else
//         this->hp = init_hp;
//     if (init_exp > 900)
//         this->exp = 900;
//     else
//         this->exp = init_exp;

//     this->moving_rule = moving_rule;
// }

Position Watson::getNextPosition()
{
    Position newPos = getCurrentPosition();
    if (new_moving_rule[0] == 'U')
    {
        newPos.setRow(newPos.getRow() - 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'D')
    {
        newPos.setRow(newPos.getRow() + 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'L')
    {
        newPos.setCol(newPos.getCol() - 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }
    else if (new_moving_rule[0] == 'R')
    {
        newPos.setCol(newPos.getCol() + 1);
        if (!getMap()->isValid(newPos, dynamic_cast<MovingObject *>(this)))
        {
            newPos = Position::npos;
        }
    }

    Position prePos = newPos;

    return newPos;
}

void Watson::move()
{
    if (!(this->getNextPosition() == Position::npos))
        this->setPosition(getNextPosition());

    // moving_rule += moving_rule[0];
    // moving_rule = moving_rule.substr(1);

    new_moving_rule += new_moving_rule[0];
    new_moving_rule = new_moving_rule.substr(1);
}
string Watson::str() const
{
    // trả về chuỗi "Watson[index=<index>;pos=<pos>;moving_rule=<moving_rule>]"
    string a1 = "[index=" + to_string(getIndex());
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";

    // string pos = "(" + to_string(init_pos.getRow()) + "," + to_string(init_pos.getCol()) + ")";

    string a2 = ";pos=" + pos;
    string a3 = ";moving_rule=" + moving_rule + "]";
    string result = "Watson" + a1 + a2 + a3;
    return result;
}
MovingObjectType Watson::getObjectType() const
{
    return WATSON;
}
int Watson::getHP() const { return hp; }
int Watson::getEXP() const { return exp; }
void Watson::setHP(int hp)
{
    if (hp > 500)
        this->hp = 500;
    else
        this->hp = hp;
}
void Watson::setEXP(int exp)
{
    if (exp > 900)
        this->exp = 900;
    else
        this->exp = exp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Map
Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->map = new MapElement **[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        map[i] = new MapElement *[num_cols];
    }
    // moi phan tu la PATH
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            map[i][j] = new Path();
        }
    }
    // gan phan tu la FAKEWALL
    for (int i = 0; i < num_fake_walls; i++)
    {
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        if (r >= 0 && r < num_rows && c >= 0 && c < num_cols)
        {
            delete map[r][c];
            int in_req_exp = (r * 257 + c * 139 + 89) % 900 + 1;
            map[r][c] = new FakeWall(in_req_exp);
        }
    }
    // gan phan tu la WALL
    for (int i = 0; i < num_walls; i++)
    {
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        if (r >= 0 && r < num_rows && c >= 0 && c < num_cols)
        {
            delete map[r][c];
            map[r][c] = new Wall();
        }
    }
}
Map::~Map()
{
    for (int r = 0; r < num_rows; r++)
    {
        for (int c = 0; c < num_cols; c++)
        {
            delete map[r][c];
        }
    }
    for (int r = 0; r < num_rows; r++)
    {
        delete[] map[r];
    }
    delete[] map;
}

int Map::getNumRows() const
{
    return num_rows;
}
int Map::getNumCols() const
{
    return num_cols;
}
ElementType Map::getElementType(int i, int j) const
{
    return map[i][j]->getType();
}
bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    // kiểm tra đối tượng có thể di chuyển vào vị trí hay không
    int i = pos.getRow(), j = pos.getCol();
    // i,j nam ngoai ma tran
    if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        return false;

    MovingObjectType object = mv_obj->getObjectType();
    if (object != SHERLOCK && object != WATSON && object != CRIMINAL && object != ROBOT)
        return false;
    ElementType type = map[i][j]->getType();
    if (type == PATH)
        return true;
    else if (type == FAKE_WALL)
    {
        if (object == CRIMINAL || object == SHERLOCK || object == ROBOT)
            return true;
        else
        {
            int in_req_exp = (i * 257 + j * 139 + 89) % 900 + 1;
            Watson *w = dynamic_cast<Watson *>(mv_obj);
            // cout << endl;
            // cout << "w->getEXP(): " << w->getEXP();
            if (w->getEXP() > in_req_exp)
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Criminal kế thừa class Character
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "Criminal")
{
    this->sherlock = sherlock;
    this->watson = watson;
    this->count = 0;
}
Position Criminal::getNextPosition()
{
    // MovingObject *mvObj = new Criminal(this->index, this->pos, this->map, this->sherlock, this->watson);
    Position posUp = this->getCurrentPosition();
    posUp.setRow(posUp.getRow() - 1);
    Position posLeft = this->getCurrentPosition();
    posLeft.setCol(posLeft.getCol() - 1);
    Position posDown = this->getCurrentPosition();
    posDown.setRow(posDown.getRow() + 1);
    Position posRight = this->getCurrentPosition();
    posRight.setCol(posRight.getCol() + 1);

    int distance[4];
    distance[0] = manhattanDistance(posUp, sherlock->getCurrentPosition()) + manhattanDistance(posUp, watson->getCurrentPosition());
    distance[1] = manhattanDistance(posLeft, sherlock->getCurrentPosition()) + manhattanDistance(posLeft, watson->getCurrentPosition());
    distance[2] = manhattanDistance(posDown, sherlock->getCurrentPosition()) + manhattanDistance(posDown, watson->getCurrentPosition());
    distance[3] = manhattanDistance(posRight, sherlock->getCurrentPosition()) + manhattanDistance(posRight, watson->getCurrentPosition());

    Position pos[4];
    pos[0] = posUp;
    pos[1] = posLeft;
    pos[2] = posDown;
    pos[3] = posRight;
    int maxDistance = -1;
    Position newPos;
    for (int i = 0; i < 4; i++)
    {
        if (distance[i] > maxDistance && getMap()->isValid(pos[i], dynamic_cast<MovingObject *>(this)))
        {
            maxDistance = distance[i];
            newPos = pos[i];
        }
    }
    if (maxDistance == -1)
        return Position::npos;

    return newPos;
}
void Criminal::move()
{
    if (this->getNextPosition() == Position::npos)
        return;
    prev_pos = this->getCurrentPosition();
    this->setPosition(this->getNextPosition());
    count++;
}

string Criminal::str() const
{
    // TODO: trả về chuỗi "Criminal[index=<index>;pos=<pos>]"
    string a1 = "[index=" + to_string(getIndex());
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    string a2 = ";pos=" + pos + "]";
    string result = "Criminal" + a1 + a2;
    return result;
}
MovingObjectType Criminal::getObjectType() const
{
    return CRIMINAL;
}
int Criminal::getCount() const
{
    return count;
}
bool Criminal::isCreatedRobotNext()
{
    if (count % 3 == 2 && count > 0 && !(getNextPosition() == Position::npos))
        return true;
    return false;
}

Position Criminal::getPrevPosition() const
{
    return prev_pos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Robot kế thừa class MovingObject
// Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name = "")
//     : MovingObject(index, pos, map, name)
// {

//     this->robot_type = robot_type;
//     this->criminal = criminal;
// }

Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    if (criminal->isCreatedRobotNext() == true)
    {
        if (criminal->getCount() == 2)
        {
            return new RobotC(index, criminal->getCurrentPosition(), map, criminal);
        }
        int toSherlock = manhattanDistance(criminal->getCurrentPosition(), sherlock->getCurrentPosition());
        int toWatson = manhattanDistance(criminal->getCurrentPosition(), watson->getCurrentPosition());
        if (toSherlock < toWatson)
            return new RobotS(index, criminal->getCurrentPosition(), map, criminal, sherlock);
        else if (toSherlock > toWatson)
            return new RobotW(index, criminal->getCurrentPosition(), map, criminal, watson);
        else
            return new RobotSW(index, criminal->getCurrentPosition(), map, criminal, sherlock, watson);
    }
    else
        return nullptr;
}
MovingObjectType Robot::getObjectType() const
{
    return ROBOT;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: RobotC kế thừa class Robot
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
    : Robot(index, init_pos, map, criminal)
{
    this->name = "RobotC"; // Name set specifically for RobotC instances
    this->robot_type = C;  // Assume there's an enum or similar for robot types
}
int RobotC::getDistance(Sherlock *sherlock)
{
    return manhattanDistance(this->getCurrentPosition(), sherlock->getCurrentPosition());
}

int RobotC::getDistance(Watson *watson)
{
    return manhattanDistance(this->getCurrentPosition(), watson->getCurrentPosition());
}
Position RobotC::getNextPosition()
{
    // RobotC di cung voi criminal
    // return criminal->getNextPosition();

    Position prevPosition = criminal->getPrevPosition();
    if (prevPosition == criminal->getCurrentPosition())
    {
        return Position::npos;
    }
    return prevPosition;

    // return criminal->getPrevPosition();
}
void RobotC::move()
{
    if (!(this->getNextPosition() == Position::npos))
        this->setPosition(this->getNextPosition());
}
string RobotC::str() const
{
    // trả về chuỗi "RobotC[pos=<pos>;type=C;dist=]"
    string a1 = "Robot[pos=";
    if (this->getCurrentPosition() == Position::npos)
    {
        string pos = "(-1, -1)";
    }
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    string a2 = ";type=C;dist=]";
    string result = a1 + pos + a2;
    return result;
}
int RobotC::getDistance() const
{
    return 75;
}
RobotType RobotC::getType() const
{
    return robot_type;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: RobotW kế thừa class Robot
RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson)
    : Robot(index, init_pos, map, criminal), watson(watson)
{
    this->name = "RobotW"; // Name set specifically for RobotW instances
    this->robot_type = W;  // Assume there's an enum or similar for robot types
}

Position RobotW::getNextPosition()
{
    // tìm vị trí tiếp theo gần Watson nhất
    Position posUp = this->getCurrentPosition();
    posUp.setRow(posUp.getRow() - 1);
    Position posLeft = this->getCurrentPosition();
    posLeft.setCol(posLeft.getCol() - 1);
    Position posDown = this->getCurrentPosition();
    posDown.setRow(posDown.getRow() + 1);
    Position posRight = this->getCurrentPosition();
    posRight.setCol(posRight.getCol() + 1);

    int distance[4];
    distance[0] = manhattanDistance(posUp, watson->getCurrentPosition());
    distance[3] = manhattanDistance(posLeft, watson->getCurrentPosition());
    distance[2] = manhattanDistance(posDown, watson->getCurrentPosition());
    distance[1] = manhattanDistance(posRight, watson->getCurrentPosition());

    Position pos[4];
    pos[0] = posUp;
    pos[3] = posLeft;
    pos[2] = posDown;
    pos[1] = posRight;

    int minDistance = 20000;
    Position newPos;
    for (int i = 0; i < 4; i++)
    {
        if (distance[i] < minDistance && map->isValid(pos[i], dynamic_cast<MovingObject *>(this)))
        {
            minDistance = distance[i];
            newPos = pos[i];
        }
    }
    if (minDistance == 20000)
        return Position::npos;
    return newPos;
}

void RobotW::move()
{
    if (!(getNextPosition() == Position::npos))
        setPosition(getNextPosition());
}

string RobotW::str() const
{
    // trả về chuỗi "RobotW[pos=<pos>;type=W;dist=<distance>]"
    string a1 = "Robot[pos=";
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    string a2 = ";type=W;dist=" + to_string(this->getDistance()) + "]";
    string result = a1 + pos + a2;
    return result;
}

RobotType RobotW::getType() const
{
    return robot_type;
}

int RobotW::getDistance() const
{
    return manhattanDistance(this->getCurrentPosition(), watson->getCurrentPosition());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: RobotS kế thừa class Robot
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock)
    : Robot(index, init_pos, map, criminal), sherlock(sherlock)
{
    this->name = "RobotS"; // Name set specifically for RobotS instances
    this->robot_type = S;  // Assume there's an enum or similar for robot types
}
Position RobotS::getNextPosition()
{
    // tìm vị trí tiếp theo gần Sherlock nhất
    Position posUp = this->getCurrentPosition();
    posUp.setRow(posUp.getRow() - 1);
    Position posLeft = this->getCurrentPosition();
    posLeft.setCol(posLeft.getCol() - 1);
    Position posDown = this->getCurrentPosition();
    posDown.setRow(posDown.getRow() + 1);
    Position posRight = this->getCurrentPosition();
    posRight.setCol(posRight.getCol() + 1);

    int distance[4];
    distance[0] = manhattanDistance(posUp, sherlock->getCurrentPosition());
    distance[3] = manhattanDistance(posLeft, sherlock->getCurrentPosition());
    distance[2] = manhattanDistance(posDown, sherlock->getCurrentPosition());
    distance[1] = manhattanDistance(posRight, sherlock->getCurrentPosition());

    Position pos[4], newPos;
    pos[0] = posUp;
    pos[3] = posLeft;
    pos[2] = posDown;
    pos[1] = posRight;

    int minDistance = 20000;
    for (int i = 0; i < 4; i++)
    {
        if (distance[i] < minDistance && map->isValid(pos[i], dynamic_cast<MovingObject *>(this)))
        {
            minDistance = distance[i];
            newPos = pos[i];
        }
    }
    if (minDistance == 20000)
        return Position::npos;
    return newPos;
}
void RobotS::move()
{
    if (!(getNextPosition() == Position::npos))
        setPosition(getNextPosition());
}

string RobotS::str() const
{
    // trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
    string a1 = "Robot[pos=";
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    string a2 = ";type=S;dist=" + to_string(this->getDistance()) + "]";
    string result = a1 + pos + a2;
    return result;
}

RobotType RobotS::getType() const
{
    return robot_type;
}

int RobotS::getDistance() const
{
    return manhattanDistance(this->getCurrentPosition(), sherlock->getCurrentPosition());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: RobotSW kế thừa class Robot
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
    : Robot(index, init_pos, map, criminal), sherlock(sherlock), watson(watson)
{
    this->name = "RobotSW"; // Name set specifically for RobotSW instances
    this->robot_type = SW;  // Assume there's an enum or similar for robot types
}

// Position RobotSW::getNextPosition()
// {
//     // tìm vị trí tổng giá trị khoảng cách Sherlock và Watson nhỏ nhất
//     Position posUp = this->getCurrentPosition();
//     posUp.setRow(posUp.getRow() - 2);
//     Position posLeft = this->getCurrentPosition();
//     posLeft.setCol(posLeft.getCol() - 2);
//     Position posDown = this->getCurrentPosition();
//     posDown.setRow(posDown.getRow() + 2);
//     Position posRight = this->getCurrentPosition();
//     posRight.setCol(posRight.getCol() + 2);

//     int distance[4];
//     distance[0] = manhattanDistance(posUp, sherlock->getCurrentPosition()) + manhattanDistance(posUp, watson->getCurrentPosition());
//     distance[3] = manhattanDistance(posLeft, sherlock->getCurrentPosition()) + manhattanDistance(posLeft, watson->getCurrentPosition());
//     distance[2] = manhattanDistance(posDown, sherlock->getCurrentPosition()) + manhattanDistance(posDown, watson->getCurrentPosition());
//     distance[1] = manhattanDistance(posRight, sherlock->getCurrentPosition()) + manhattanDistance(posRight, watson->getCurrentPosition());

//     Position pos[4], newPos;
//     pos[0] = posUp;
//     pos[3] = posLeft;
//     pos[2] = posDown;
//     pos[1] = posRight;

//     int minDistance = 20000;
//     for (int i = 0; i < 4; i++)
//     {
//         if (distance[i] < minDistance && map->isValid(pos[i], dynamic_cast<MovingObject *>(this)))
//         {
//             minDistance = distance[i];
//             newPos = pos[i];
//         }
//     }
//     if (minDistance == 20000)
//         return Position::npos;
//     return newPos;
// }

Position RobotSW::getNextPosition()
{
    // tìm vị trí tổng giá trị khoảng cách Sherlock và Watson nhỏ nhất
    Position posUp = this->getCurrentPosition();
    posUp.setRow(posUp.getRow() - 2);

    Position posDown = this->getCurrentPosition();
    posDown.setRow(posDown.getRow() + 2);

    Position posLeft = this->getCurrentPosition();
    posLeft.setCol(posLeft.getCol() - 2);

    Position posRight = this->getCurrentPosition();
    posRight.setCol(posRight.getCol() + 2);

    Position posCheoTraiTren = this->getCurrentPosition();
    posCheoTraiTren.setRow(posCheoTraiTren.getRow() - 1);
    posCheoTraiTren.setCol(posCheoTraiTren.getCol() - 1);
    posCheoTraiTren.setRow(posCheoTraiTren.getRow() - 1);
    posCheoTraiTren.setCol(posCheoTraiTren.getCol() - 1);

    Position posCheoPhaiTren = this->getCurrentPosition();
    posCheoPhaiTren.setRow(posCheoPhaiTren.getRow() - 1);
    posCheoPhaiTren.setCol(posCheoPhaiTren.getCol() + 1);
    posCheoPhaiTren.setRow(posCheoPhaiTren.getRow() - 1);
    posCheoPhaiTren.setCol(posCheoPhaiTren.getCol() + 1);

    Position posCheoTraiDuoi = this->getCurrentPosition();
    posCheoTraiDuoi.setRow(posCheoTraiDuoi.getRow() + 1);
    posCheoTraiDuoi.setCol(posCheoTraiDuoi.getCol() - 1);
    posCheoTraiDuoi.setRow(posCheoTraiDuoi.getRow() + 1);
    posCheoTraiDuoi.setCol(posCheoTraiDuoi.getCol() - 1);

    Position posCheoPhaiDuoi = this->getCurrentPosition();
    posCheoPhaiDuoi.setRow(posCheoPhaiDuoi.getRow() + 1);
    posCheoPhaiDuoi.setCol(posCheoPhaiDuoi.getCol() + 1);
    posCheoPhaiDuoi.setRow(posCheoPhaiDuoi.getRow() + 1);
    posCheoPhaiDuoi.setCol(posCheoPhaiDuoi.getCol() + 1);

    Position posUpLeft = this->getCurrentPosition();
    posUpLeft.setRow(posUpLeft.getRow() - 1);
    posUpLeft.setCol(posUpLeft.getCol() - 1);

    Position posUpRight = this->getCurrentPosition();
    posUpRight.setRow(posUpRight.getRow() - 1);
    posUpRight.setCol(posUpRight.getCol() + 1);

    Position posDownLeft = this->getCurrentPosition();
    posDownLeft.setRow(posDownLeft.getRow() + 1);
    posDownLeft.setCol(posDownLeft.getCol() - 1);

    Position posDownRight = this->getCurrentPosition();
    posDownRight.setRow(posDownRight.getRow() + 1);
    posDownRight.setCol(posDownRight.getCol() + 1);

    int distances[12];
    distances[0] = manhattanDistance(posUp, sherlock->getCurrentPosition()) + manhattanDistance(posUp, watson->getCurrentPosition());
    distances[1] = manhattanDistance(posDown, sherlock->getCurrentPosition()) + manhattanDistance(posDown, watson->getCurrentPosition());
    distances[2] = manhattanDistance(posLeft, sherlock->getCurrentPosition()) + manhattanDistance(posLeft, watson->getCurrentPosition());
    distances[3] = manhattanDistance(posRight, sherlock->getCurrentPosition()) + manhattanDistance(posRight, watson->getCurrentPosition());
    distances[4] = manhattanDistance(posUpLeft, sherlock->getCurrentPosition()) + manhattanDistance(posUpLeft, watson->getCurrentPosition());
    distances[5] = manhattanDistance(posUpRight, sherlock->getCurrentPosition()) + manhattanDistance(posUpRight, watson->getCurrentPosition());
    distances[6] = manhattanDistance(posDownLeft, sherlock->getCurrentPosition()) + manhattanDistance(posDownLeft, watson->getCurrentPosition());
    distances[7] = manhattanDistance(posDownRight, sherlock->getCurrentPosition()) + manhattanDistance(posDownRight, watson->getCurrentPosition());
    distances[8] = manhattanDistance(posCheoPhaiDuoi, sherlock->getCurrentPosition()) + manhattanDistance(posCheoPhaiDuoi, watson->getCurrentPosition());
    distances[9] = manhattanDistance(posCheoPhaiTren, sherlock->getCurrentPosition()) + manhattanDistance(posCheoPhaiTren, watson->getCurrentPosition());
    distances[10] = manhattanDistance(posCheoTraiDuoi, sherlock->getCurrentPosition()) + manhattanDistance(posCheoTraiDuoi, watson->getCurrentPosition());
    distances[11] = manhattanDistance(posCheoTraiTren, sherlock->getCurrentPosition()) + manhattanDistance(posCheoTraiTren, watson->getCurrentPosition());

    // OUTPUT << distances[2] << endl;
    Position pos[12] = {posUp, posDown, posLeft, posRight, posUpLeft, posUpRight, posDownLeft, posDownRight, posCheoPhaiDuoi, posCheoPhaiTren, posCheoTraiDuoi, posCheoTraiTren};
    int minDistance = 20000;
    Position newPos = Position::npos;

    for (int i = 0; i < 8; i++)
    {
        if (distances[i] < minDistance && map->isValid(pos[i], dynamic_cast<MovingObject *>(this)))
        {
            minDistance = distances[i];
            newPos = pos[i];
        }
    }

    if (minDistance == 20000)
        return Position::npos;

    return newPos;
}

void RobotSW::move()
{
    if (!(getNextPosition() == Position::npos))
        setPosition(getNextPosition());
}
string RobotSW::str() const
{
    // trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
    string a1 = "Robot[pos=";
    string pos = "(" + to_string(this->getCurrentPosition().getRow()) + "," + to_string(this->getCurrentPosition().getCol()) + ")";
    string a2 = ";type=SW;dist=" + to_string(this->getDistance()) + "]";
    string result = a1 + pos + a2;
    return result;
}
RobotType RobotSW::getType() const
{
    return robot_type;
}
int RobotSW::getDistance() const
{
    return manhattanDistance(this->pos, sherlock->getCurrentPosition()) + manhattanDistance(this->pos, watson->getCurrentPosition());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: ArrayMovingObject
ArrayMovingObject::ArrayMovingObject(int capacity)
{
    this->capacity = capacity;
    arr_mv_objs = new MovingObject *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        arr_mv_objs[i] = nullptr;
    }
    count = 0;
}
// ArrayMovingObject::~ArrayMovingObject()
// {
//     for (int i = 0; i < capacity; i++)
//     {
//         delete arr_mv_objs[i];
//     }
//     delete[] arr_mv_objs;
// }
bool ArrayMovingObject::isFull() const
{
    if (count == capacity)
        return true;
    return false;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    if (count >= capacity)
        return false;
    arr_mv_objs[count] = mv_obj;
    count++;
    return true;
}
MovingObject *ArrayMovingObject::get(int index) const
{
    if (index < 0 || index >= capacity)
        return nullptr;
    return arr_mv_objs[index];
}

int ArrayMovingObject::size() const
{
    return count;
}

string ArrayMovingObject::str() const
{
    string result = "ArrayMovingObject[count=" + to_string(count) + ";" + "capacity=" + to_string(capacity) + ";";

    for (int i = 0; i < count; i++)
    {
        if (i == count - 1)
        {
            result = result + arr_mv_objs[i]->str() + "]";
        }
        else
        {
            result = result + arr_mv_objs[i]->str() + ";";
        }
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS: Configuration
Configuration::Configuration(const string &filepath)
{
    ifstream file(filepath);
    string s;
    while (file >> s)
    {
        stringstream ss(s);
        string strRow[2], tmp;
        int i = 0;
        while (getline(ss, tmp, '='))
        {
            strRow[i] = tmp;
            i++;
        }
        if (strRow[0] == "MAP_NUM_ROWS")
        {
            map_num_rows = stoi(strRow[1]);
        }
        else if (strRow[0] == "MAP_NUM_COLS")
        {
            map_num_cols = stoi(strRow[1]);
        }
        else if (strRow[0] == "MAX_NUM_MOVING_OBJECTS")
        {
            max_num_moving_objects = stoi(strRow[1]);
        }
        else if (strRow[0] == "ARRAY_WALLS")
        {
            susu[0] = strRow[1];
            int n = strRow[1].length();
            string sub = strRow[1].substr(1, n - 2);
            stringstream ss1(sub);
            num_walls = 0;
            while (getline(ss1, tmp, ';'))
            {
                num_walls++;
            }
            arr_walls = new Position[num_walls];
            stringstream ss2(sub);
            int k = 0;
            while (getline(ss2, tmp, ';'))
            {
                string sub2 = tmp.substr(1, tmp.size() - 2);
                stringstream ss3(sub2);
                int t = 0;
                while (getline(ss3, tmp, ','))
                {
                    if (t == 0)
                    {
                        arr_walls[k].setRow(stoi(tmp));
                        t++;
                    }
                    else
                        arr_walls[k].setCol(stoi(tmp));
                }
                k++;
            }
        }
        else if (strRow[0] == "ARRAY_FAKE_WALLS")
        {
            susu[1] = strRow[1];
            int n = strRow[1].length();
            string sub = strRow[1].substr(1, n - 2);
            stringstream ss1(sub);
            num_fake_walls = 0;
            while (getline(ss1, tmp, ';'))
            {
                num_fake_walls++;
            }
            arr_fake_walls = new Position[num_fake_walls];
            stringstream ss2(sub);
            int k = 0;
            while (getline(ss2, tmp, ';'))
            {
                string sub2 = tmp.substr(1, tmp.size() - 2);
                stringstream ss3(sub2);
                int t = 0;
                while (getline(ss3, tmp, ','))
                {
                    if (t == 0)
                    {
                        arr_fake_walls[k].setRow(stoi(tmp));
                        t++;
                    }
                    else
                        arr_fake_walls[k].setCol(stoi(tmp));
                }
                k++;
            }
        }
        else if (strRow[0] == "SHERLOCK_MOVING_RULE")
        {
            sherlock_moving_rule = strRow[1];
        }
        else if (strRow[0] == "SHERLOCK_INIT_POS")
        {
            susu[2] = strRow[1];
            int n = strRow[1].size();
            string sub = strRow[1].substr(1, n - 2);
            stringstream ss(sub);
            int k = 0;
            while (getline(ss, tmp, ','))
            {
                if (k == 0)
                {
                    sherlock_init_pos.setRow(stoi(tmp));
                    k++;
                }
                else
                    sherlock_init_pos.setCol(stoi(tmp));
            }
        }
        else if (strRow[0] == "SHERLOCK_INIT_HP")
        {
            sherlock_init_hp = stoi(strRow[1]);
        }
        else if (strRow[0] == "SHERLOCK_INIT_EXP")
        {
            sherlock_init_exp = stoi(strRow[1]);
        }
        else if (strRow[0] == "WATSON_MOVING_RULE")
        {
            watson_moving_rule = strRow[1];
        }
        else if (strRow[0] == "WATSON_INIT_POS")
        {
            susu[3] = strRow[1];
            int n = strRow[1].size();
            string sub = strRow[1].substr(1, n - 2);
            stringstream ss(sub);
            int k = 0;
            while (getline(ss, tmp, ','))
            {
                if (k == 0)
                {
                    watson_init_pos.setRow(stoi(tmp));
                    k++;
                }
                else
                    watson_init_pos.setCol(stoi(tmp));
            }
        }
        else if (strRow[0] == "WATSON_INIT_HP")
        {
            watson_init_hp = stoi(strRow[1]);
        }
        else if (strRow[0] == "WATSON_INIT_EXP")
        {
            watson_init_exp = stoi(strRow[1]);
        }
        else if (strRow[0] == "CRIMINAL_INIT_POS")
        {
            susu[4] = strRow[1];
            int n = strRow[1].size();
            string sub = strRow[1].substr(1, n - 2);
            stringstream ss(sub);
            int k = 0;
            while (getline(ss, tmp, ','))
            {
                if (k == 0)
                {
                    criminal_init_pos.setRow(stoi(tmp));
                    k++;
                }
                else
                    criminal_init_pos.setCol(stoi(tmp));
            }
        }
        else if (strRow[0] == "NUM_STEPS")
        {
            num_steps = stoi(strRow[1]);
        }
    }
    file.close();
}

Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}
string Configuration::str() const
{
    stringstream ss;
    ss << "Configuration[" << endl;
    ss << "MAP_NUM_ROWS=" << to_string(map_num_rows) << endl;
    ss << "MAP_NUM_COLS=" << to_string(map_num_cols) << endl;
    ss << "MAX_NUM_MOVING_OBJECTS=" << to_string(max_num_moving_objects) << endl;
    ss << "NUM_WALLS=" << to_string(num_walls) << endl;
    ss << "ARRAY_WALLS=" << susu[0] << endl;
    ss << "NUM_FAKE_WALLS=" << to_string(num_fake_walls) << endl;
    ss << "ARRAY_FAKE_WALLS=" << susu[1] << endl;
    ss << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << endl;
    ss << "SHERLOCK_INIT_POS=" << susu[2] << endl;
    ss << "SHERLOCK_INIT_HP=" << to_string(sherlock_init_hp) << endl;
    ss << "SHERLOCK_INIT_EXP=" << to_string(sherlock_init_exp) << endl;
    ss << "WATSON_MOVING_RULE=" << watson_moving_rule << endl;
    ss << "WATSON_INIT_POS=" << susu[3] << endl;
    ss << "WATSON_INIT_HP=" << to_string(watson_init_hp) << endl;
    ss << "WATSON_INIT_EXP=" << to_string(watson_init_exp) << endl;
    ss << "CRIMINAL_INIT_POS=" << susu[4] << endl;
    ss << "NUM_STEPS=" << to_string(num_steps) << endl;
    ss << "]";
    return ss.str();
}

// *CLASS: MagicBook
ItemType MagicBook::getType() const
{
    // TODO: get (1 dòng)
    return MAGIC_BOOK;
}
string MagicBook::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "MagicBook";
}
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, exp

    //   Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    //     return sherlock->getEXP() <= 350;
    if (robot != nullptr)
    {
        return false; // Không cho phép sử dụng MagicBook nếu đang có robot
    }
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock && sherlock->getEXP() <= 350)
    {
        return true; // Sherlock có thể sử dụng MagicBook nếu exp <= 350
    }
    else if (watson && watson->getEXP() <= 350)
    {
        return true; // Watson có thể sử dụng MagicBook nếu exp <= 350
    }

    return false; // Trả về false nếu không thỏa mãn điều kiện
}
void MagicBook::use(Character *obj, Robot *robot)
{
    // TODO: tăng exp
    // int newexp = obj->getEXP() + (obj->getEXP() * 25 / 100);
    // obj->setEXP(newexp);
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock)
    {
        // int newexp = sherlock->getEXP() + (sherlock->getEXP() * 25 / 100);

        int newexp = ceilf(double(sherlock->getEXP() + ceilf(double(sherlock->getEXP() * 25.00 / 100.00))));

        sherlock->setEXP(newexp);
    }
    else if (watson)
    {
        // int newexp = watson->getEXP() + (watson->getEXP() * 25 / 100);

        int newexp = ceilf(double(watson->getEXP() + ceilf(double(watson->getEXP() * 25.00 / 100.00))));

        watson->setEXP(newexp);
    }
}
// *CLASS: EnergyDrink
ItemType EnergyDrink::getType() const
{
    // TODO: get (1 dòng)
    return ENERGY_DRINK;
}
string EnergyDrink::str() const
{
    // TODO: trả về chuỗi biển diễn (1 dòng)
    return "EnergyDrink";
}
bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, hp
    // return obj->getHP() <= 100;
    if (robot != nullptr)
    {
        return false; // Không cho phép sử dụng MagicBook nếu đang có robot
    }
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock && sherlock->getHP() <= 100)
    {
        return true; // Sherlock có thể sử dụng MagicBook nếu exp <= 350
    }
    else if (watson && watson->getHP() <= 100)
    {
        return true; // Watson có thể sử dụng MagicBook nếu exp <= 350
    }

    return false; // Trả về false nếu không thỏa mãn điều kiện
}
void EnergyDrink::use(Character *obj, Robot *robot)
{
    // TODO: tăng hp
    // int newhp = obj->getHP() + (obj->getHP() * 20 / 100); // Increase hp by 20%
    // obj->setHP(newhp);

    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock)
    {
        // int newhp = sherlock->getHP() + (sherlock->getHP() * 20 / 100);
        int newhp = ceilf(double(sherlock->getHP() + ceilf(double(sherlock->getHP() * 20.00 / 100.00))));
        sherlock->setHP(newhp);
    }
    else if (watson)
    {
        // int newhp = watson->getHP() + (watson->getHP() * 25 / 100);
        int newhp = ceilf(double(watson->getHP() + ceilf(double(watson->getHP() * 20.00 / 100.00))));
        watson->setHP(newhp);
    }
}
// *CLASS: FirstAid
ItemType FirstAid::getType() const
{
    // TODO: get (1 dòng)
    return FIRST_AID;
}
string FirstAid::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "FirstAid";
}
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, exp || hp
    // return obj->getHP() <= 100 || obj->getEXP() <= 350;
    if (robot != nullptr)
    {
        return false; // Không cho phép sử dụng MagicBook nếu đang có robot
    }
    Watson *watson = dynamic_cast<Watson *>(obj);
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);

    if (sherlock && (sherlock->getHP() <= 100 || sherlock->getEXP() <= 350))
    {
        return true; // Sherlock có thể sử dụng MagicBook nếu exp <= 350
    }

    if (watson && (watson->getHP() <= 100 || watson->getEXP() <= 350))
    {
        return true; // Watson có thể sử dụng MagicBook nếu exp <= 350
    }

    return false; // Trả về false nếu không thỏa mãn điều kiện
}
void FirstAid::use(Character *obj, Robot *robot)
{
    // TODO: tăng hp
    // int newhp = obj->getHP() + (obj->getHP() * 50 / 100); // Increase hp by 50%
    // obj->setHP(newhp);

    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock)
    {
        int newhp = ceilf(double(sherlock->getHP() + ceilf(double(sherlock->getHP() * 50.00 / 100.00))));
        sherlock->setHP(newhp);
    }
    else if (watson)
    {
        int newhp = ceilf(double(watson->getHP() + ceilf(double(watson->getHP() * 50.00 / 100.00))));
        watson->setHP(newhp);
    }
}
// *CLASS: ExcemptionCard
ItemType ExcemptionCard::getType() const
{
    // TODO: get (1 dòng)
    return EXCEMPTION_CARD;
}
string ExcemptionCard::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "ExcemptionCard";
}
bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Trước khi đấm Robot, Sherlock, hp lẻ
    // return dynamic_cast<Sherlock *>(obj) != nullptr && (obj->getHP() % 2 != 0);
    Sherlock *sherlock = dynamic_cast<Sherlock *>(obj);
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (sherlock != nullptr && robot != nullptr)
    {
        return (sherlock->getHP() % 2 != 0);
    }
    return false;
}
void ExcemptionCard::use(Character *obj, Robot *robot)
{
    // TODO: sinh viên hiện thực theo tư duy code của mình (hàm có thể rỗng)
}
// *CLASS: PassingCard

PassingCard::PassingCard(int i, int j)
{
    // TODO: constructor gán giá trị cho thuộc tính challenge (i,j là tọa độ)
    int t = (i * 11 + j) % 4;
    switch (t)
    {
    case 0:
        challenge = "RobotS";
        break;
    case 1:
        challenge = "RobotC";
        break;
    case 2:
        challenge = "RobotSW";
        break;
    case 3:
        challenge = "all";
        break;
    }
}

ItemType PassingCard::getType() const
{
    // TODO: get (1 dòng)
    return PASSING_CARD;
}
string PassingCard::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    // return "PassingCard: " + challenge;

    return "PassingCard";
}
string robotTypeToString(RobotType type)
{
    switch (type)
    {
    case C:
        return "RobotC";
    case S:
        return "RobotS";
    case W:
        return "RobotW";
    case SW:
        return "RobotSW";
    default:
        return "Unknown";
    }
}
bool PassingCard::canUse(Character *obj, Robot *robot)
{
    Watson *watson = dynamic_cast<Watson *>(obj);
    if (watson && watson->getHP() % 2 == 0 && robot != nullptr)
    {
        return true;
    }
    return false;
}

void PassingCard::use(Character *obj, Robot *robot)
{
    Watson *watson = dynamic_cast<Watson *>(obj);
    string robotType = robotTypeToString(robot->getType()); // Sử dụng hàm chuyển đổi
    if (watson == nullptr)
    {
        return;
    }

    if (watson)

    {
        if (robotType == challenge || challenge == "all")
        {
        }
        else
        {
            int currentExp = watson->getEXP();
            if (currentExp - 50 <= 0)
            {
                currentExp = 50;
            }
            watson->setEXP(currentExp - 50);
        }
    }
}
// *CLASS: BaseBag
BaseBag::BaseBag(int capacity)
{
    // TODO: constructor gán giá trị cho CÁC THUỘC TÍNH
    this->capacity = capacity;
    this->size = 0;
    this->head = nullptr;
}
bool BaseBag::insert(BaseItem *item)
{
    // TODO: thêm Node chứa item vào đầu Linked List
    if (size >= capacity)
        return false;
    // Node *newNode = new Node(item, head);
    // head = newNode;
    // size++;
    // return true;

    // Node *newNode = new Node(item, head);
    // if (head == nullptr)
    // {
    //     head = newNode;
    // }
    // else
    // {
    //     newNode->next = head;
    //     head = newNode;
    // }
    // size++;
    // return true;

    Node *temp = new Node(item);
    temp->item = item;
    temp->next = head;
    head = temp;
    size++;
    return true;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    if (!head)
        return nullptr;
    Node *current = head, *prev = nullptr;
    while (current != nullptr)
    {
        if (current->item->getType() == itemType)
        {
            BaseItem *itemToReturn = current->item;
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                swap(head->item, current->item);
                prev = head;
                head = head->next;
            }
            delete prev;
            size--;
            return itemToReturn;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}

string BaseBag::str() const
{
    // TODO: trả về chuỗi biểu diễn
    // *"Bag[count=<thuộc tính size>;<danh sách tên các item cách nhau bởi dấu ,>]"
    if (head == nullptr)
        return "Bag[count=0;]";
    std::stringstream ss;
    ss << "Bag[count=" << size << ";";
    Node *current = head;
    while (current)
    {
        ss << current->item->str();
        if (current->next)
            ss << ",";
        current = current->next;
    }
    ss << "]";
    return ss.str();
}
bool BaseBag::containsItemType(ItemType type) const
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->item->getType() == type)
        {
            return true; // Tìm thấy item có loại phù hợp
        }
        current = current->next;
    }
    return false; // Không tìm thấy item phù hợp
}
// *CLASS: SherlockBag
SherlockBag::SherlockBag(Sherlock *character)
    : BaseBag(13
              // TODO: constructor class cha

      )
{
    // TODO: constructor class con
    this->sherlock = character;
}

BaseItem *SherlockBag::get()
{
    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->item->canUse(sherlock, nullptr))
        {
            BaseItem *itemToReturn = current->item;

            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                // prev->next = current->next;
                swap(head->item, current->item);
                prev = head;
                head = head->next;
            }

            delete prev;
            size--;
            return itemToReturn;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}
// *CLASS: WatsonBag
WatsonBag::WatsonBag(Watson *character)
    : BaseBag(15
              // TODO: constructor class cha
      )
{
    // TODO: constructor class con
    this->watson = character;
}

BaseItem *WatsonBag::get()
{
    Node *current = head;
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->item->canUse(watson, nullptr))
        {
            BaseItem *itemToReturn = current->item;

            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                // prev->next = current->next;
                swap(head->item, current->item);
                prev = head;
                head = head->next;
            }

            delete prev;
            size--;
            return itemToReturn;
        }
        prev = current;
        current = current->next;
    }
    return nullptr;
}
Robot::Robot(int index, const Position &pos, Map *map, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), criminal(criminal), poshead(pos)
{
    // khởi tạo item

    int i = pos.getRow();
    int j = pos.getCol();
    int p = i * j;
    int s = dominantDigitSum(p);
    if (s >= 0 && s <= 1)
    {
        item = new MagicBook();
        item_type = MAGIC_BOOK;
    }
    else if (s >= 2 && s <= 3)
    {
        item = new EnergyDrink();
        item_type = ENERGY_DRINK;
    }
    else if (s >= 4 && s <= 5)
    {
        item = new FirstAid();
        item_type = FIRST_AID;
    }
    else if (s >= 6 && s <= 7)
    {
        item = new ExcemptionCard();
        item_type = EXCEMPTION_CARD;
    }
    else if (s >= 8 && s <= 9)
    {
        // cout << "robot co passingcard" << endl;

        item_type = PASSING_CARD;
        item = new PassingCard(i, j);
        // cout << "passing o vi tri " << i << " " << j << endl;
    }
    else
    {
        item_type = MAGIC_BOOK;
    }

    // init_pos_x = i;
    // init_pos_y = j;

    // TODO: tính toán loại item
}

int Robot::dominantDigitSum(int n)
{
    while (n >= 10)
    {
        int sum = 0;
        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    }
    return n;
}
BaseItem *Robot::NewItem()
{
    switch (item_type)
    {
    case MAGIC_BOOK:
        return new MagicBook();
    case ENERGY_DRINK:
        return new EnergyDrink();
    case FIRST_AID:
        return new FirstAid();
    case EXCEMPTION_CARD:
        return new ExcemptionCard();
    case PASSING_CARD:
        // cout << "passing card " << poshead.getRow() << " " << poshead.getCol() << endl;
        return new PassingCard(poshead.getRow(), poshead.getCol());
    default:
        return nullptr;
    }
}

// Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
//     : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
// {
//     // TODO: thêm thuộc tính bag
//     // this->bag = bag;
//     if (init_hp > 500)
//         this->hp = 500;
//     else
//         this->hp = init_hp;
//     if (init_exp > 900)
//         this->exp = 900;
//     else
//         this->exp = init_exp;

//     this->moving_rule = moving_rule;

//     this->bag = new SherlockBag(this);
// }

Sherlock::Sherlock(int index, const std::string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    // Khởi tạo các thành viên khác...
    if (init_hp > 500)
        this->hp = 500;
    else
        this->hp = init_hp;
    if (init_exp > 900)
        this->exp = 900;
    else
        this->exp = init_exp;

    this->moving_rule = moving_rule;

    this->bag = new SherlockBag(this);

    new_moving_rule = moving_rule;

    init_position = init_pos;
}

Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    // TODO: thêm thuộc tính bag
    // this->bag = bag;
    if (init_hp > 500)
        this->hp = 500;
    else
        this->hp = init_hp;
    if (init_exp > 900)
        this->exp = 900;
    else
        this->exp = init_exp;

    this->moving_rule = moving_rule;

    this->bag = new WatsonBag(this);

    new_moving_rule = moving_rule;

    init_position = init_pos;
}

// bool compareInitPositions(Sherlock *sherlock, Watson *watson)
// {
//     return sherlock->getInitPosition() == watson->getInitPosition();
// }
StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    stopChecker = false;
}
StudyPinkProgram::~StudyPinkProgram()
{
    delete map;
    delete config;
    delete arr_mv_objs;
}
bool StudyPinkProgram::isStop() const
{
    // Kiểm tra HP của Sherlock
    if (sherlock->getHP() == 0)
    {
        return true;
    }

    // Kiểm tra HP của Watson
    if (watson->getHP() == 0)
    {
        return true;
    }

    for (int i = 0; i < arr_mv_objs->size(); ++i)
    {
        if (arr_mv_objs->checkMeet(i))
        {
            return true;
        }
    }

    return false;
}

// void StudyPinkProgram::printMap(ofstream &OUTPUT) const
// {
//     for (int i = -1; i < config->map_num_cols; i++)
//     {
//         if (i == -1)
//             OUTPUT << setw(7) << ""
//                    << "|";
//         else
//             OUTPUT << setw(7) << i << "|";
//     }
//     OUTPUT << endl;
//     for (int i = 0; i < config->map_num_rows; i++)
//     {
//         OUTPUT << setw(7) << i << "|";
//         for (int j = 0; j < config->map_num_cols; j++)
//         {
//             int idx = map->getElementType(i, j);
//             string nameElement[3] = {"     ", "IIIII", "-----"};
//             string nameChar[4] = {"S", "W", "C", "R"};
//             string robotName[4] = {"0", "1", "2", "3"};
//             string cellValue = nameElement[idx];
//             Position charPos(i, j);
//             for (int k = 0; k < arr_mv_objs->size(); k++)
//             {
//                 if (arr_mv_objs->get(k)->getCurrentPosition().isEqual(charPos))
//                 {
//                     if (cellValue == "     " || cellValue == "-----" || cellValue == "IIIII")
//                         cellValue = "";
//                     idx = arr_mv_objs->get(k)->getObjectType();
//                     if (idx == 3)
//                     {
//                         MovingObject *temp = arr_mv_objs->get(k);
//                         while (cellValue[cellValue.length() - 1] == ' ')
//                         {
//                             cellValue = cellValue.substr(0, cellValue.length() - 1);
//                         }
//                         cellValue += robotName[dynamic_cast<Robot *>(temp)->getType()];
//                         continue;
//                     }
//                     cellValue += nameChar[idx];
//                 }
//             }
//             if (!(cellValue == "     " || cellValue == "-----" || cellValue == "IIIII"))
//                 cellValue = "" + cellValue + "";
//             OUTPUT << setw(7) << cellValue << "|";
//         }
//         OUTPUT << endl;
//     }
// }

// void StudyPinkProgram::run(bool verbose, ofstream &OUTPUT)
// {
//     if (!OUTPUT.is_open())
//     {
//         return;
//     }

//     // OUTPUT << config->str() << endl;

//     stopChecker = sherlock->getHP() == 0 || watson->getHP() == 0;

//     for (int istep = 0; istep < config->num_steps && !stopChecker; ++istep)
//     {
//         int roundSize = arr_mv_objs->size();
//         for (int i = 0; i < roundSize && !stopChecker; ++i)
//         {
//             stringstream ss(arr_mv_objs->str());

//             MovingObject *robot = nullptr;
//             if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
//             {
//                 MovingObject *newRobot = Robot::create(arr_mv_objs->size(), map, dynamic_cast<Criminal *>(arr_mv_objs->get(i)), sherlock, watson);
//                 if (newRobot)
//                 {
//                     arr_mv_objs->add(newRobot);
//                     roundSize++;
//                 }
//             }

//             MovingObject *obj = arr_mv_objs->get(i);

//             arr_mv_objs->get(i)->move();

//             // stopChecker = arr_mv_objs->checkMeet(i);

//             stopChecker = arr_mv_objs->checkMeet(i);
//             // if (!stopChecker)
//             // {
//             //     break;
//             // }

//             printInfo(istep, i, OUTPUT);

//             // printMap(OUTPUT);

//             // OUTPUT << stopChecker;

//             // if (robot != nullptr)
//             // {
//             //     if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
//             //     {
//             //         arr_mv_objs->add(robot);
//             //     }
//             //     else
//             //     {
//             //         // delete robot;
//             //     }
//             // }
//         }
//         // OUTPUT << "thoat";

//         if (isStop())
//         {
//             printResult();
//         }
//     }
// }

void StudyPinkProgram::run(bool verbose)
{

    for (int isstep = 0; isstep < config->num_steps; ++isstep)
        for (int i = 0; i < arr_mv_objs->size(); ++i)
        {
            arr_mv_objs->get(i)->move();
            if (isStop())
            {
                printStep(isstep);
                break;
            }
            if (verbose)
            {
                printStep(isstep);
            }
        }
    printResult();
}

// *------------------------------------------------------------------
// *
// *------------------------------------------------------------------
// !-----------------------------------
// ! Lưu ý về việc xét thông số khi tăng giảm
// ! Các thay đổi thông số là dựa trên thông số hiện tại
// ! Các thông số không phải số nguyên THỰC HIỆN LÀM TRÒN LÊN -> NHÂN VẬT CHỈ HI SINH KHI INIT hp = 0
// !-----------------------------------
// *CLASS: ArrayMovingObject

bool ArrayMovingObject::checkMeet(int index)
{
    if (index < 0 || index >= count || arr_mv_objs[index] == nullptr)
    {
        return false;
    }

    MovingObject *currentObj = arr_mv_objs[index];
    Position currentPos = currentObj->getCurrentPosition();

    for (int i = 0; i < this->count; i++)
    {
        if (i == index || arr_mv_objs[i] == nullptr)
            continue; // Skip self and null objects.

        MovingObject *otherObj = arr_mv_objs[i];
        if (currentPos.isEqual(otherObj->getCurrentPosition()))
        { // Check if positions match.
            if (currentObj->getObjectType() == otherObj->getObjectType())
            {
                continue;
            }

            if (auto sherlock = dynamic_cast<Sherlock *>(currentObj))
            {
                if (auto robot = dynamic_cast<Robot *>(otherObj))
                {
                    // Cast to specific robot types and call the appropriate meet method.
                    if (auto robotC = dynamic_cast<RobotC *>(robot))
                    {
                        sherlock->meet(robotC); // Special case for RobotC that might return true.
                    }
                    else if (auto robotS = dynamic_cast<RobotS *>(robot))
                    {
                        sherlock->meet(robotS);
                    }
                    else if (auto robotW = dynamic_cast<RobotW *>(robot))
                    {
                        sherlock->meet(robotW);
                    }
                    else if (auto robotSW = dynamic_cast<RobotSW *>(robot))
                    {
                        sherlock->meet(robotSW);
                    }
                    // return false;
                }
                if (auto watson = dynamic_cast<Watson *>(otherObj))
                {
                    sherlock->meet(watson);
                    // return false;
                }
                if (auto criminal = dynamic_cast<Criminal *>(otherObj))
                {
                    // cout << "dung o sherlock ";

                    return true; // Sherlock meets the criminal.
                }
            }
            else if (auto watson = dynamic_cast<Watson *>(currentObj))
            {
                if (auto robot = dynamic_cast<Robot *>(otherObj))
                {
                    // Watson meets different types of robots.
                    if (auto robotC = dynamic_cast<RobotC *>(robot))
                    {
                        watson->meet(robotC);
                    }
                    else if (auto robotS = dynamic_cast<RobotS *>(robot))
                    {
                        watson->meet(robotS);
                    }
                    else if (auto robotW = dynamic_cast<RobotW *>(robot))
                    {

                        watson->meet(robotW);
                    }
                    else if (auto robotSW = dynamic_cast<RobotSW *>(robot))
                    {
                        watson->meet(robotSW);
                    }
                    // return false; // Watson's interactions with robots do not capture criminals.
                }
                if (auto sherlock = dynamic_cast<Sherlock *>(otherObj))
                {
                    watson->meet(sherlock);
                    // return false; // Exchange items, return false.
                }
                if (auto criminal = dynamic_cast<Criminal *>(otherObj))
                {

                    // cout << "dung o watson ";
                    return true; // Watson meets the criminal.
                }
            }
            else if (auto criminal = dynamic_cast<Criminal *>(currentObj))
            {

                // cout << "dung o criminal ";
                if (auto robot = dynamic_cast<Robot *>(otherObj))
                {
                    // If Criminal meets a Robot, ignore and continue checking.
                    return false;
                }
                else if (auto sherlock = dynamic_cast<Sherlock *>(otherObj))
                {
                    // If Criminal meets Sherlock, return true.
                    // cout << "Criminal meets Sherlock.";
                    return true;
                }
                else if (auto watson = dynamic_cast<Watson *>(otherObj))
                {
                    // If Criminal meets Watson, also return true.
                    // cout << "Criminal meets Watson.";
                    return true;
                }
            }
            else if (auto robot = dynamic_cast<Robot *>(currentObj))
            {
                // Handling interactions between robots and characters.
                if (auto sherlock = dynamic_cast<Sherlock *>(otherObj))
                {
                    // Sherlock meets different types of robots.
                    if (auto robotC = dynamic_cast<RobotC *>(robot))
                    {
                        sherlock->meet(robotC);
                    }
                    else if (auto robotS = dynamic_cast<RobotS *>(robot))
                    {
                        sherlock->meet(robotS);
                    }
                    else if (auto robotW = dynamic_cast<RobotW *>(robot))
                    {
                        sherlock->meet(robotW);
                    }
                    else if (auto robotSW = dynamic_cast<RobotSW *>(robot))
                    {
                        sherlock->meet(robotSW);
                    }
                    // return false;
                }
                if (auto watson = dynamic_cast<Watson *>(otherObj))
                {
                    // Watson meets different types of robots.
                    if (auto robotC = dynamic_cast<RobotC *>(robot))
                    {
                        watson->meet(robotC);
                    }
                    else if (auto robotS = dynamic_cast<RobotS *>(robot))
                    {
                        watson->meet(robotS);
                    }
                    else if (auto robotW = dynamic_cast<RobotW *>(robot))
                    {
                        watson->meet(robotW);
                    }
                    else if (auto robotSW = dynamic_cast<RobotSW *>(robot))
                    {
                        watson->meet(robotSW);
                    }
                    // return false;
                }
                if (auto criminal = dynamic_cast<Criminal *>(otherObj))
                {
                    // cout << "dung o sherlock ";
                    if (auto robotC = dynamic_cast<RobotC *>(robot))
                    {
                        return false;
                    }
                    else if (auto robotS = dynamic_cast<RobotS *>(robot))
                    {
                        return false;
                    }
                    else if (auto robotW = dynamic_cast<RobotW *>(robot))
                    {
                        return false;
                    }
                    else if (auto robotSW = dynamic_cast<RobotSW *>(robot))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return false; // No significant interaction occurred.
}

// *CLASS: Sherlock
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
void Sherlock::setPos(Position pos)
{
    // TODO: Sử dụng trong trường hợp thắng RobotC sẽ dịch chuyển đến vị trí Criminal
    this->pos = pos;

    if (this->map->isValid(pos, this))
    {
        this->pos = pos;
    }
}

// bool Sherlock::meet(RobotS *robotS)
// {
//     TODO: Xử lý khi gặp robot S

//     if (this->exp > 400)
//     {
//     BaseItem *item = robotS->NewItem();
//          if (item)
//          {
//              this->bag->insert(item);
//              return true;
//          }
//     }

//      else
//      {
//          ExcemptionCard *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
//          if (!card)
//          {
//             int lostexp = static_cast<int>(exp * 0.1);
//              setEXP(exp - lostexp);
//          }

//          BaseItem *usableItem = this->bag->get();
//          if (usableItem)
//         {
//              usableItem->use(this, nullptr);
//         }
//          return false;
//      }
// }
bool Sherlock::meet(RobotS *robotS)
{

    // bool hasCard = false;
    // BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));

    // if (card)
    // {
    //     hasCard = true;
    // }

    // nếu thắng nhận item

    // BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
    // if (card)
    // {
    //     card->use(this, nullptr);
    // }

    if (this->exp > 400)
    {
        // sử dụng excemptioncard

        // nhận item từ robot
        BaseItem *item = robotS->NewItem();
        if (item)
        {
            this->bag->insert(item);
        }

        BaseItem *usableItem = this->bag->get();
        if (usableItem)
        {
            usableItem->use(this, robotS);
        }
        return true;
    }
    // nếu thua sử card hoặc mất máu
    if (this->exp <= 400)
    {
        // trước đụng độ
        BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
        if (card)
        {
            card->use(this, nullptr);
        }

        // sau đụng độ
        if (!card)
        {
            int lostexp = static_cast<int>(exp * 0.1);
            setEXP(exp - lostexp);
        }
        // xem thử item nào sử dụng dc
        BaseItem *usableItem = this->bag->get();
        if (usableItem)
        {
            usableItem->use(this, robotS);
        }
    }

    return false;
}
bool Sherlock::meet(RobotW *robotW)
{
    // TODO: Xử lý khi gặp robot W
    BaseItem *item = robotW->NewItem();
    if (item)
    {
        this->bag->insert(item);
    }

    BaseItem *usableItem = this->bag->get();
    if (usableItem)
    {
        usableItem->use(this, robotW);
    }
    return true;
}
bool Sherlock::meet(RobotSW *robotSW)
{
    // TODO: Xử lý khi gặp robot SW
    if (this->exp > 300 && this->hp > 335)
    {
        // nếu có excemptioncard thì dùng

        // BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
        // if (card)
        // {
        //     card->use(this, nullptr);
        // }

        // nếu thắng sẽ nhân item
        BaseItem *item = robotSW->NewItem();
        if (item)
        {
            this->bag->insert(item);
        }
        return true;
    }
    // nếu thua
    else
    {
        // BaseItem *exemptioncard = this->bag->get(EXCEMPTION_CARD);

        // nếu có excemptioncard sẽ dùng
        BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
        if (card)
        {
            card->use(this, robotSW);
        }

        if (!card)
        {
            this->setHP(this->hp - (int)(this->hp * 0.15));
            this->setEXP(this->exp - (int)(this->exp * 0.15));

            BaseItem *usefulItem = this->bag->get();
            if (usefulItem)
            {
                usefulItem->use(this, robotSW);
            }
        }
        // return false;
    }

    return false;
}
bool Sherlock::meet(RobotC *robotC)
{
    // TODO: Xử lý khi gặp robot C

    // nếu thắng robot exp > 500
    if (this->exp > 500)
    {
        // sử dụng nếu có trong túi
        BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
        if (card)
        {
            card->use(this, robotC);
        }
        return true;
    }
    else
    {
        // sử dụng card nếu có trong túi
        BaseItem *card = dynamic_cast<ExcemptionCard *>(this->bag->get(EXCEMPTION_CARD));
        if (card)
        {
            card->use(this, nullptr);
        }
        // nhận item từ robot
        BaseItem *item = robotC->NewItem();
        if (item)
        {
            this->bag->insert(item);
        }
        // tìm item dùng được trong túi
        BaseItem *usefulItem = this->bag->get();
        if (usefulItem)
        {
            usefulItem->use(this, robotC);
        }

        return false;
    }
}
bool Sherlock::meet(Watson *watson)
{
    // TODO: Xử lý trao đổi thẻ ExcemptionCard
    // TODO: KHI CẢ 2 ĐỀU CÓ THỂ TRAO ĐỔI && ĐỔI TOÀN BỘ NẾU NHIỀU HƠN 1 (KỂ CẢ KHI ĐỐI PHƯƠNG)

    bool exchanged = false; // Biến kiểm tra xem có sự trao đổi nào xảy ra không
    bool sherlockHasPassingCard = this->bag->containsItemType(PASSING_CARD);
    bool watsonHasExemptionCard = watson->getBag()->containsItemType(EXCEMPTION_CARD);

    if (sherlockHasPassingCard && watsonHasExemptionCard)
    {
        BaseItem *item;
        while ((item = this->bag->get(PASSING_CARD)) != nullptr)
        {
            if (!watson->getBag()->insert(item))
            {
                // Nếu túi của Watson đầy, trả lại item vào túi của Sherlock và dừng trao đổi
                this->bag->insert(item);
                break;
            }
            exchanged = true;
        }

        // Watson tặng ExemptionCard cho Sherlock
        while ((item = watson->getBag()->get(EXCEMPTION_CARD)) != nullptr)
        {

            // this->bag->insert(item);
            if (!this->bag->insert(item))
            {
                // Nếu túi của Sherlock đầy, trả lại item vào túi của Watson và dừng trao đổi
                watson->getBag()->insert(item);
                break;
            }

            exchanged = true;
        }

        // return exchanged; // Trả về true nếu trao đổi diễn ra (mặc dù không kiểm tra có thẻ nào được trao đổi hay không)}
    }

    return exchanged;
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    // TODO: Xử lý trao đổi khi gặp robot S
    // sử dụng passingcard
    BaseItem *card = dynamic_cast<PassingCard *>(this->bag->get(PASSING_CARD));
    if (card)
    {
        card->use(this, nullptr);
    }
    // xem thử item nào sử dụng dc
    BaseItem *usableItem = this->bag->get();
    if (usableItem)
    {
        usableItem->use(this, nullptr);
    }
    return true;
}
bool Watson::meet(RobotW *robotW)
{
    // TODO: Xử lý trao đổi khi gặp robot W

    if (this->hp > 350)
    {
        // sử dụng excemptioncard

        // nhận item từ robot
        BaseItem *item = robotW->NewItem();

        // int i = 0;
        // i++;
        if (item)
        {
            // cout << "co item " << item->getType() << endl;

            // cout << " item " << i << " " << item << endl;

            this->bag->insert(item);

            BaseItem *usableItem = this->bag->get();
            if (usableItem)
            {
                usableItem->use(this, robotW);
            }
            return true;
        }
    }
    // nếu thua sử card hoặc mất máu
    if (this->hp <= 350)
    {
        BaseItem *card = dynamic_cast<PassingCard *>(this->bag->get(PASSING_CARD));
        if (card)
        {
            card->use(this, robotW);

            // BaseItem *usableItem = this->bag->get();
            // if (usableItem)
            // {
            //     usableItem->use(this, nullptr);
            // }
            // return true;
        }

        // sau đụng độ
        if (!card)
        {
            int losthp = static_cast<int>(hp * 0.05);
            setHP(hp - losthp);
        }
        // xem thử item nào sử dụng dc
        BaseItem *usableItem = this->bag->get();
        if (usableItem)
        {
            usableItem->use(this, nullptr);
        }

        // return false;
    }

    return false;
}
bool Watson::meet(RobotSW *robotSW)
{
    // cout << "da vao " << endl;
    // TODO: Xử lý trao đổi khi gặp robot SW
    // cout << "watson hp: " << this->hp << "watson exp: " << this->exp << endl;

    if ((this->exp > 600) && (this->hp > 165))
    {
        // sử dụng passingcard

        BaseItem *card = dynamic_cast<PassingCard *>(this->bag->get(PASSING_CARD));
        if (card)
        {
            card->use(this, robotSW);
        }

        // nhận item từ robot
        BaseItem *item = robotSW->NewItem();
        if (item)
        {
            this->bag->insert(item);
        }
        return true;
    }
    // nếu thua sử card hoặc mất máu
    else
    {
        // trước đụng độ
        BaseItem *card = dynamic_cast<PassingCard *>(this->bag->get(PASSING_CARD));
        if (card)
        {
            card->use(this, robotSW);
        }

        BaseItem *item = robotSW->NewItem();
        if (item)
        {
            this->bag->insert(item);
        }

        // sau đụng độ
        if (!card)
        {
            int lostexp = static_cast<int>(exp * 0.15);
            // cout << "Lost exp " << lostexp << " " << endl;
            int losthp = static_cast<int>(hp * 0.15);
            setEXP(exp - lostexp);
            setHP(hp - losthp);
        }
        // xem thử item nào sử dụng dc
        BaseItem *usableItem = this->bag->get();
        if (usableItem)
        {
            usableItem->use(this, nullptr);
        }

        return false;
    }
}
bool Watson::meet(RobotC *robotC)
{
    // TODO: Xử lý trao đổi khi gặp robot C

    // sử dụng passingcard

    // BaseItem *card = dynamic_cast<PassingCard *>(this->bag->get(PASSING_CARD));
    // if (card)
    // {
    //     card->use(this, nullptr);
    // }

    // nhận item từ robotC
    BaseItem *item = robotC->NewItem();
    if (item)
    {
        this->bag->insert(item);
    }

    // sử dụng item
    BaseItem *usableItem = this->bag->get();
    if (usableItem)
    {
        usableItem->use(this, nullptr);
    }
    return true;
}
bool Watson::meet(Sherlock *sherlock)
{
    // TODO: Xử lý trao đổi khi gặp Sherlock
    bool exchanged = false; // Biến kiểm tra xem có sự trao đổi nào xảy ra không

    bool sherlockHasPassingCard = sherlock->getBag()->containsItemType(PASSING_CARD);
    bool watsonHasExemptionCard = this->bag->containsItemType(EXCEMPTION_CARD);

    if (sherlockHasPassingCard && watsonHasExemptionCard)
    {
        BaseItem *item;
        while ((item = sherlock->getBag()->get(PASSING_CARD)) != nullptr)
        {
            if (!this->bag->insert(item))
            {
                // Nếu túi của Watson đầy, trả lại item vào túi của Sherlock và dừng trao đổi
                this->bag->insert(item);
                break;
            }
            exchanged = true;
        }

        // Watson tặng ExemptionCard cho Sherlock
        while ((item = this->bag->get(EXCEMPTION_CARD)) != nullptr)
        {
            if (!sherlock->getBag()->insert(item))
            {
                // Nếu túi của Sherlock đầy, trả lại item vào túi của Watson và dừng trao đổi
                this->bag->insert(item);
                break;
            }
            exchanged = true;
        }

        // return exchanged; // Trả về true nếu trao đổi diễn ra (mặc dù không kiểm tra có thẻ nào được trao đổi hay không)
    }

    return exchanged;
}

BaseBag *Sherlock::getBag() const
{
    // TODO: get bag
    return bag;
}
BaseBag *Watson::getBag() const
{
    // TODO: get bag
    return bag;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////