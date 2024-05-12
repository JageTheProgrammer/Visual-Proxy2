#include "events.h"
#include "dialog.h"
#include "json.hpp"
#include "gt.hpp"
#include "proton/hash.hpp"
#include "proton/rtparam.hpp"
#include "proton/variant.hpp"
#include "server.h"
#include <vector> 
#include "utils.h"
#include <thread>
#include <limits.h>
#include "HTTPRequest.hpp"
#include "items_dat_decode.h"
#include "namespace_class.h"
#include "cpphook.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "player.h"
#include "world.h"
#include <windows.h>
#include <shellapi.h>
#include "Pathfinder/PathFinder.h"


#include "proxy.cpp"
#include "Discord.h"

bool gems_accumulating = false;
int gems_accumulated_count = 0;
bool bj = false;
int type_delay = 250;
int roulettex = 0;
int roulettey = 0;
int typenumber = 36;
int color_type = 4;
bool type = false;
int yuzde2 = 10;
int notaxx = 0;
int notaxy = 0;
int lampx = 0;
int lampy = 0;
int lampx2 = 0;
int lampy2 = 0;
int punchx = 0;
int punchy = 0;
bool csn_punch = false;
int selectednumber = 6;
bool reme = false, legit = false, qq = false;
int yposautohoster = 0, xposautohoster = 0;
std::vector<int> intToDigits(int num_)
{
    std::vector<int> ret;
    string iStr = to_string(num_);

    for (int i = iStr.size() - 1; i >= 0; --i)
    {
        int units = pow(10, i);
        int digit = num_ / units % 10;
        ret.push_back(digit);
    }

    return ret;
}
static bool seeinchest = false;

void send_vset() {
    if (iswear) {
        int skincolor = 1685231359;
        variantlist_t liste{ "OnSetClothing" };
        liste[1] = vector3_t{ hair,  shirt,  pants };
        liste[2] = vector3_t{ shoe,  face,  hand };
        liste[3] = vector3_t{ back,  mask,  neck };
        liste[4] = skincolor;
        liste[5] = vector3_t{ ances , 1.f, 0.f };

        g_server->send(true, liste, g_server->m_world.local.netid, -1);
        g_server->sendState(g_server->m_world.local.netid);
    }
}
bool events::out::variantlist(gameupdatepacket_t* packet) {
    variantlist_t varlist{};
    varlist.serialize_from_mem(utils::get_extended(packet));
    /*if (iswear) {
        int skincolor = 1685231359;
        variantlist_t liste{ "OnSetClothing" };
        liste[1] = vector3_t{ hair,  shirt,  pants };
        liste[2] = vector3_t{ shoe,  face,  hand };
        liste[3] = vector3_t{ back,  mask,  neck };
        liste[4] = skincolor;
        liste[5] = vector3_t{ ances , 1.f, 0.f };

        g_server->send(true, liste, g_server->m_world.local.netid, -1);
        g_server->sendState(g_server->m_world.local.netid);
    }*/
    if (debug)
        PRINTS("varlist: %s\n", varlist.print().c_str());
    return false;
}

bool events::out::pingreply(gameupdatepacket_t* packet) {
    //since this is a pointer we do not need to copy memory manually again
    packet->m_vec2_x = 1000.f;  //gravity
    packet->m_vec2_y = 250.f;   //move speed
    packet->m_vec_x = 64.f;     //punch range
    packet->m_vec_y = 64.f;     //build range
    packet->m_jump_amount = 0;  //for example unlim jumps set it to high which causes ban
    packet->m_player_flags = 0; //effect flags. good to have as 0 if using mod noclip, or etc.
    return false;
}
bool fastdrop = false;
bool banscam = false;

bool hostermode = false;
void force() {


    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    fastdrop = false;
}

void forceacc()
{

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    bruhmoment = false;
}
bool isInside(int circle_x, int circle_y, int rad, int x, int y) {
    // Compare radius of circle with distance
    // of its center from given point
    if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad)
        return true;
    else
        return false;
}
void SendPacket(int a1, string a2, ENetPeer* enetPeer)
{
    if (enetPeer)
    {
        ENetPacket* v3 = enet_packet_create(0, a2.length() + 5, 1);
        memcpy(v3->data, &a1, 4);
        //*(v3->data) = (DWORD)a1;
        memcpy((v3->data) + 4, a2.c_str(), a2.length());

        //cout << std::hex << (int)(char)v3->data[3] << endl;
        enet_peer_send(enetPeer, 0, v3);
    }
}
void DropItem(int id, int count) {
    g_server->send(false, "action|drop\n|itemID|" + to_string(id));
    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|" + to_string(id) + "|\ncount|" + to_string(count));
}
void save_details() {
    ifstream ifs("save/config.json");
    if (ifs.is_open()) {
        json j;
        ifs >> j;
        j["save1"] = vclothes;
        j["save2"] = vclothes;
        j["save3"] = vclothes;
        j["load1"] = vclothes;
        j["load2"] = vclothes;
        j["load3"] = vclothes;
        j["wm"] = wrench;
        j["ptp"] = pathfinding;
        j["modas"] = modas;
        j["modas3"] = ban_all;
        j["modas2"] = exit_world;
        ofstream f_("save/config.json");
        f_ << j;
        f_.close();
    }

}

void load1() {
    ofstream ifs("config.json");
    if (ifs.is_open()) {
        json j;
        ifs << j;
        ifs.close();
    }
}
void load2() {
    ofstream ifs("config.json");
    if (ifs.is_open()) {
        json j;
        ifs << j;
        ifs.close();
    }
}
void load3() {
    ofstream ifs("config.json");
    if (ifs.is_open()) {
        json j;
        ifs << j;
        ifs.close();
    }
}
int balance() {
    int wl = 0;
    wl += g_server->local_player.inventory.getItemCount(242);
    wl += g_server->local_player.inventory.getItemCount(1796) * 100;
    wl += g_server->local_player.inventory.getItemCount(7188) * 10000;
    return wl;
}

int item_count(int itemid) {
    int wl = g_server->local_player.inventory.getItemCount(itemid);
    return wl;
}

bool daw()
{
    if (item_count(242) > 0) {
        dropwl = true;
        g_server->send(false, "action|drop\n|itemID|242");
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + to_string(item_count(242))); //242
    }
    if (item_count(1796) > 0) {
        dropdl = true;
        g_server->send(false, "action|drop\n|itemID|1796");
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + to_string(item_count(1796))); //242
    }
    if (item_count(7188) > 0) {
        dropwl = true;
        g_server->send(false, "action|drop\nitemID|7188");
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + to_string(item_count(7188))); //242
    }
    return true;
}
std::chrono::steady_clock::time_point gems_last_collected_time;
void CheckAndSendGemsMessage() {
    if (gems_accumulating) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - gems_last_collected_time).count();

        if (elapsed_time >= 1) { // Change the duration as needed
            gt::send_log("`9Collected `2+" + to_string(gems_accumulated_count) + " `9Gems");
            gems_accumulated_count = 0;
            gems_accumulating = false;
        }
        else {
            for (auto& obj : g_server->m_world.objects) {
                if (obj.second.itemID == 112) {
                    gems_accumulated_count += obj.second.count;
                    gems_last_collected_time = std::chrono::steady_clock::now();
                    gems_accumulating = true;
                }
            }
        }
    }
}


void placeaga(int id, int posx, int posy) {
    if (posx == 0 || posy == 0)
    {
        gt::send_log("position cannot be null!");
        return;
    }
    auto pos = g_server->m_world.local.pos;
    GameUpdatePacket legitpacket{ 0 };
    legitpacket.type = PACKET_STATE;
    legitpacket.item_id = id;
    legitpacket.int_x = posx;
    legitpacket.int_y = posy;
    legitpacket.vec_x = pos.m_x;
    legitpacket.vec_y = pos.m_y;
    legitpacket.flags = 2592;
    // her þey doðruda aaqq

    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&legitpacket, sizeof(GameUpdatePacket));

}
void title_() {
    Sleep(10);
    if (title == "legend") {
        variantlist_t va{ "OnNameChanged" };
        va[1] = "``" + g_server->local_player.name + " of Legend``";
        g_server->send(true, va, g_server->local_player.netid, -1);
    }
    if (title == "bluename") {
        variantlist_t va{ "OnCountryState" };
        va[1] = "ae|showGuild|maxLevel";
        g_server->send(true, va, g_server->local_player.netid, -1);
    }
    if (title == "dr") {
        variantlist_t va{ "OnCountryState" };
        va[1] = "ae|showGuild|doctor";
        g_server->send(true, va, g_server->local_player.netid, -1);
    }
}
void place_tile(int id, int posx, int posy) {
    if (posx == 0 || posy == 0)
    {
        gt::send_log("position cannot be null!");
        return;
    }
    auto pos = g_server->m_world.local.pos;

    g_server->enterDoor(false, posx, posy);


    GameUpdatePacket legitpacket{ 0 };
    legitpacket.type = PACKET_STATE;
    legitpacket.item_id = id;
    legitpacket.int_x = posx;
    legitpacket.int_y = posy;
    legitpacket.vec_x = pos.m_x;
    legitpacket.vec_y = pos.m_y;
    legitpacket.flags = 2592;
    // her þey doðruda aaqq
    if (legit)
    {
        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&legitpacket, sizeof(GameUpdatePacket));
    }
    GameUpdatePacket packet{ 0 };
    packet.type = PACKET_TILE_CHANGE_REQUEST;
    packet.item_id = id;
    packet.int_x = posx;
    packet.int_y = posy;
    packet.vec_x = pos.m_x;
    packet.vec_y = pos.m_y;
    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(GameUpdatePacket));
}
void do_auto_collect() {
    if (g_server->m_world.connected) {
        auto pos2f = g_server->local_player.GetPos();
        for (const auto& object : g_server->m_world.objects) {
            if (isInside(object.second.pos.m_x, object.second.pos.m_y, 5 * 32, pos2f.m_x, pos2f.m_y)) {
                gameupdatepacket_t packet{ 0 };
                packet.m_vec_x = object.second.pos.m_x;
                packet.m_vec_y = object.second.pos.m_y;
                packet.m_type = 11;
                packet.m_player_flags = -1;
                packet.m_int_data = object.second.uid;
                packet.m_state1 = object.second.pos.m_x + object.second.pos.m_y + 4;

                g_server->send(false, NET_MESSAGE_GAME_PACKET, reinterpret_cast<uint8_t*>(&packet), sizeof(gameupdatepacket_t));
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}



/*void farm_auto() {

    while (farmauto) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (done) {
            int posx = g_server->m_world.local.pos.m_x / 32;
            int posy = g_server->m_world.local.pos.m_y / 32;
            place_tile(farmid, posx + 1, posy);
            done = false;
        }
        else {
            int posx = g_server->m_world.local.pos.m_x / 32;
            int posy = g_server->m_world.local.pos.m_y / 32;
            break_tile(farmid, posx + 1, posy);
            done = true;
        }
    }
}*/
void TpRetard(float x, float y)
{
    vector2_t pos;
    pos.m_x = x;
    pos.m_y = y;
    variantlist_t varlist{ "OnSetPos" };
    varlist[1] = pos;
    g_server->m_world.local.pos = pos;
    g_server->send(true, varlist, g_server->m_world.local.netid, -1);
}


int events::out::get_punch_id(const int id_) {
    switch (id_) {
    case 138: return 1;
    case 366:
    case 1464:
        return 2;
    case 472: return 3;
    case 594:
    case 10130:
    case 5424:
    case 5456:
    case 4136:
    case 10052:
        return 4;
    case 768: return 5;
    case 900:
    case 7760:
    case 9272:
    case 5002:
    case 7758:
        return 6;
    case 910:
    case 4332:
        return 7;
    case 930:
    case 1010:
    case 6382:
        return 8;
    case 1016:
    case 6058:
        return 9;
    case 1204:
    case 9534:
        return 10;
    case 1378: return 11;
    case 1440: return 12;
    case 1484:
    case 5160:
    case 9802:
        return 13;
    case 1512:
    case 1648:
        return 14;
    case 1542: return 15;
    case 1576: return 16;
    case 1676:
    case 7504:
        return 17;
    case 1748:
    case 8006:
    case 8008:
    case 8010:
    case 8012:
        return 19;
    case 1710:
    case 4644:
    case 1714:
    case 1712:
    case 6044:
    case 1570:
        return 18;
    case 1780: return 20;
    case 1782:
    case 5156:
    case 9776:
    case 9782:
    case 9810:
        return 21;
    case 1804:
    case 5194:
    case 9784:
        return 22;
    case 1868:
    case 1998:
        return 23;
    case 1874: return 24;
    case 1946:
    case 2800:
        return 25;
    case 1952:
    case 2854:
        return 26;
    case 1956: return 27;
    case 1960: return 28;
    case 2908:
    case 6312:
    case 9496:
    case 8554:
    case 3162:
    case 9536:
    case 4956:
    case 3466:
    case 4166:
    case 4506:
    case 2952:
    case 9520:
    case 9522:
    case 8440:
    case 3932:
    case 3934:
    case 8732:
    case 3108:
    case 9766:
    case 12368:
        return 29;
    case 1980: return 30;
    case 2066:
    case 4150:
    case 11082:
    case 11080:
    case 11078:
        return 31;
    case 2212:
    case 5174:
    case 5004:
    case 5006:
    case 5008:
        return 32;
    case 2218: return 33;
    case 2220: return 34;
    case 2266: return 35;
    case 2386: return 36;
    case 2388: return 37;
    case 2450:
        return 38;
    case 2476:
    case 4208:
    case 12308:
    case 10336:
    case 9804:
        return 39;
    case 4748:
    case 4294:
        return 40;
    case 2512:
    case 9732:
    case 6338:
        return 41;
    case 2572: return 42;
    case 2592:
    case 9396:
    case 2596:
    case 9548:
    case 9812:
        return 43;
    case 2720: return 44;
    case 2752: return 45;
    case 2754: return 46;
    case 2756: return 47;
    case 2802: return 49;
    case 2866: return 50;
    case 2876: return 51;
    case 2878:
    case 2880:
        return 52;
    case 2906:
    case 4170:
    case 4278:
        return 53;
    case 2886: return 54;
    case 2890: return 55;
    case 2910: return 56;
    case 3066: return 57;
    case 3124: return 58;
    case 3168: return 59;
    case 3214:
    case 9194:
        return 60;
    case 7408:
    case 3238:
        return 61;
    case 3274: return 62;
    case 3300: return 64;
    case 3418: return 65;
    case 3476: return 66;
    case 3596: return 67;
    case 3686: return 68;
    case 3716: return 69;
    case 4290: return 71;
    case 4474: return 72;
    case 4464:
    case 9500:
        return 73;
    case 4746: return 75;
    case 4778:
    case 6026: case 7784:
        return 76;
    case 4996:
    case 3680:
    case 5176:
        return 77;
    case 4840: return 78;
    case 5206: return 79;
    case 5480:
    case 9770:
    case 9772:
        return 80;
    case 6110: return 81;
    case 6308: return 82;
    case 6310: return 83;
    case 6298: return 84;
    case 6756: return 85;
    case 7044: return 86;
    case 6892: return 87;
    case 6966: return 88;
    case 7088:
    case 11020:
        return 89;
    case 7098:
    case 9032:
        return 90;
    case 7192: return 91;
    case 7136:
    case 9738:
        return 92;
    case 3166: return 93;
    case 7216: return 94;
    case 7196:
    case 9340:
        return 95;
    case 7392:
    case 9604:
        return 96;
    case 7384: return 98;
    case 7414: return 99;
    case 7402: return 100;
    case 7424: return 101;
    case 7470: return 102;
    case 7488: return 103;
    case 7586:
    case 7646:
    case 9778:
        return 104;
    case 7650: return 105;
    case 6804:
    case 6358:
        return 106;
    case 7568:
    case 7570:
    case 7572:
    case 7574:
        return 107;
    case 7668: return 108;
    case 7660:
    case 9060:
        return 109;
    case 7584:
        return 110;
    case 7736:
    case 9116:
    case 9118:
    case 7826:
    case 7828:
    case 11440:
    case 11442:
    case 11312:
    case 7830:
    case 7832:
    case 10670:
    case 9120:
    case 9122:
    case 10680:
    case 10626:
    case 10578:
    case 10334:
    case 11380:
    case 11326:
    case 7912:
    case 11298:
    case 10498:
    case 12342:
        return 111;
    case 7836:
    case 7838:
    case 7840:
    case 7842:
        return 112;
    case 7950: return 113;
    case 8002: return 114;
    case 8022: return 116;
    case 8036: return 118;
    case 9348:
    case 8372:
        return 119;
    case 8038: return 120;
    case 8816:
    case 8818:
    case 8820:
    case 8822:
        return 128;
    case 8910: return 129;
    case 8942: return 130;
    case 8944:
    case 5276:
        return 131;
    case 8432:
    case 8434:
    case 8436:
    case 8950:
        return 132;
    case 8946: case 9576: return 133;
    case 8960: return 134;
    case 9006: return 135;
    case 9058: return 136;
    case 9082:
    case 9304:
        return 137;
    case 9066:
        return 138;
    case 9136: return 139;
    case 9138:
        return 140;
    case 9172: return 141;
    case 9254: return 143;
    case 9256: return 144;
    case 9236: return 145;
    case 9342: return 146;
    case 9542: return 147;
    case 9378: return 148;
    case 9376: return 149;
    case 9410: return 150;
    case 9462: return 151;
    case 9606:
        return 152;
    case 9716:
    case 5192:
        return 153;
    case 10048: return 167;
    case 10064: return 168;
    case 10046: return 169;
    case 10050: return 170;
    case 10128: return 171;
    case 10210:
    case 9544:
        return 172;
    case 10330: return 178;
    case 10398: return 179;
    case 10388:
    case 9524:
    case 9598:
        return 180;
    case 10442: return 184;
    case 10506: return 185;
    case 10652: return 188;
    case 10676: return 191;
    case 10694: return 193;
    case 10714: return 194;
    case 10724: return 195;
    case 10722: return 196;
    case 10754: return 197;
    case 10800: return 198;
    case 10888: return 199;
    case 10886:
    case 11308:
        return 200;
    case 10890: return 202;
    case 10922: case 9550: return 203;
    case 10990: return 205;
    case 10998: return 206;
    case 10952: return 207;
    case 11000: return 208;
    case 11006: return 209;
    case 11046: return 210;
    case 11052: return 211;
    case 10960: return 212;
    case 10956:
    case 9774:
        return 213;
    case 10958: return 214;
    case 10954: return 215;
    case 11076: return 216;
    case 11084: return 217;
    case 11118:
    case 9546:
    case 9574:
        return 218;
    case 11120: return 219;
    case 11116: return 220;
    case 11158: return 221;
    case 11162: return 222;
    case 11142: return 223;
    case 11232: return 224;
    case 11140: return 225;
    case 11248:
    case 9596:
    case 9636:
        return 226;
    case 11240: return 227;
    case 11250: return 228;
    case 11284: return 229;
    case 11292: return 231;
    case 11314: return 233;
    case 11316: return 234;
    case 11324: return 235;
    case 11354: return 236;
    case 11760:
    case 11464:
    case 11438:
    case 12230:
    case 11716:
    case 11718:
    case 11674:
    case 11630:
    case 11786:
    case 11872:
    case 11762:
    case 11994:
    case 12172:
    case 12184:
    case 11460:
    case 12014:
    case 12016:
    case 12018:
    case 12020:
    case 12022:
    case 12024:
    case 12246:
    case 12248:
    case 12176:
    case 12242:
    case 11622:
    case 12350:
    case 12300:
    case 12374:
    case 12356:
        return 237;
    case 11814:
    case 12232:
    case 12302:
        return 241;
    case 11548:
    case 11552:
        return 242;
    case 11704:
    case 11706:
        return 243;
    case 12180:
    case 12346:
    case 12344:
        return 244;
    case 11506:
    case 11508:
    case 11562:
    case 11768:
    case 11882:
    case 11720:
    case 11884:
        return 245;
    case 12432:
    case 12434:
        return 246;
    case 11818:
    case 11876:
    case 12000:
    case 12240:
    case 12642:
    case 12644:
        return 248;

    }
    return 0;
}

bool dropitem(int itemid, string count) {
    cdrop = true;
    g_server->send(false, "action|drop\nitemID|" + std::to_string(itemid));
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + count); //242
    return true;
}



bool unaccessing = false;
void unaccess() {
    unaccessing = true;
    g_server->send(false, "action|input\n|text|/unaccess");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    g_server->send(false, "action|dialog_return\ndialog_name|unaccess\nbuttonClicked|Yes"); //242
    gt::send_log("`2Done Unaccess.");
}
void tptopos(float x, float y)
{
    vector2_t pos;
    pos.m_x = x;
    pos.m_y = y;
    variantlist_t varlist{ "OnSetPos" };
    varlist[1] = pos;
    g_server->m_world.local.pos = pos;
    g_server->send(true, varlist, g_server->m_world.local.netid, -1);
}


bool custom_drop(int sayi, vector2_t pos, float m_x, float m_y) {

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    string cdropcount = to_string(sayi);
    if (balance() < sayi) {
        gt::send_log("`9Dont have `#balance`9. balance: " + to_string(balance()) + ".");
        return true;
    }
    if (sayi < 100) {

        if (item_count(242) < sayi) {
            gameupdatepacket_t drop{ 0 };
            drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
            drop.m_int_data = 1796;
            g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        dropwl = true;
        g_server->send(false, "action|drop\n|itemID|242");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + cdropcount); //242
        gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
    }

    else if (sayi > 10000) {


        int sayi1 = (sayi / 10000);

        int kalan = ((sayi / 100) - (sayi1 * 100));
        int kalan2 = sayi - ((kalan * 100) + (sayi1 * 10000));
        if (kalan > item_count(1796)) {
            gameupdatepacket_t drop{ 0 };
            drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
            drop.m_int_data = 7188;
            g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        else if (item_count(242) < kalan2) {
            gameupdatepacket_t drop{ 0 };
            drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
            drop.m_int_data = 1796;
            g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        dropbgl = true;
        g_server->send(false, "action|drop\n|itemID|7188");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string(sayi1)); //242

        dropdl = true;
        g_server->send(false, "action|drop\n|itemID|1796");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(kalan)); //242

        dropwl = true;
        g_server->send(false, "action|drop\n|itemID|242");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan2)); //242

        gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
    }
    else {
        int sayi1 = (sayi / 100);
        int kalan = (sayi % 100);

        if (item_count(242) < kalan) {
            gameupdatepacket_t drop{ 0 };
            drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
            drop.m_int_data = 1796;
            g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

        }
        else if (item_count(1796) < sayi1) {
            gameupdatepacket_t drop{ 0 };
            drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
            drop.m_int_data = 242;
            g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

        }
        dropdl = true;
        g_server->send(false, "action|drop\n|itemID|1796");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(sayi1)); //242

        dropwl = true;
        g_server->send(false, "action|drop\n|itemID|242");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan)); //242

        gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
    }
    total_bet = 0;
}
void checkdrop(int pos1, int pos2) {
    int p5 = 0;
    int p6 = 0;
    for (auto it = g_server->m_world.objects.begin(); it != g_server->m_world.objects.end(); ++it)
    {
        p5 = it->second.pos.m_x / 32;
        p6 = it->second.pos.m_y / 32;
        if (p5 == pos1 && p6 == pos2) {

            gt::send_log("match");
        }
        else {
            gt::send_log("nah");
        }
    }
    gt::send_log("`4check" + to_string(p5) + "," + to_string(p6));
}


bool bandymas() {
    float posx = std::atoi(host::pos1x.c_str());
    float posy = std::atoi(host::pos1y.c_str());
    g_server->m_world.local.pos.m_x = posx;
    g_server->m_world.local.pos.m_y = posy;
    variantlist_t xdd{ "OnSetPos" };
    xdd[1] = g_server->m_world.local.pos;
    g_server->send(true, xdd, g_server->m_world.local.netid, -1);
    return true;
}
void compresswltodl() {
    gameupdatepacket_t packet{};
    packet.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
    packet.m_int_data = 242;
    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(gameupdatepacket_t));
    return;
}
void shatterdltowl() {
    gameupdatepacket_t packet{};
    packet.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
    packet.m_int_data = 1796;
    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(gameupdatepacket_t));
    return;
}
bool find_command(std::string chat, std::string name) {
    bool found = chat.find("/" + name) == 0;
    if (found)
        gt::send_log("`6" + chat);
    return found;
}
void ban_everyone() {
    gt::send_log("`9You have `4(Ban All)`9 When Mod joins option `2Enabled");
    gt::send_log("`4Banning `9Everyone in the world...");
    std::string username = "all";
    for (auto& player : g_server->m_world.players) {
        auto nik = player.name.substr(2); //remove color
        string banint = player.name.substr(2).substr(0, player.name.length() - 4);
        if (nik.find(username)) {
            g_server->send(false, "action|input\n|text|/ban " + banint);
        }
    }
}

void exit_pasaulis() {
    gt::send_log("`9You have `4(Exit World)`9 When Mod joins option `2Enabled");
    gt::send_log("`bLeaving The World Now");
    g_server->send(false, "action|quit_to_exit", 3);
}
bool check_number(string num) {
    for (int i = 0; i < num.length(); i++)
        if (isdigit(num[i]) == false)
            return false;
    return true;
}
void tool_thread(int id, std::string name) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    g_server->send(false, "action|dialog_return\ndialog_name|surgery\nbuttonClicked|tool" + std::to_string(id));
}
//Antiseptic *
void send_tool(int id, std::string content) {
    std::string name = "";

    switch (id) {
    case 1258:
        name = "`9Sponge``";
        break;
    case 1260:
        name = "`7Scalpel``";
        break;
    case 1262:
        name = "`3Anesthetic``";
        break;
    case 1264:
        name = "`7Antiseptic``";
        break;
    case 1266:
        name = "`2Antibiotic``";
        break;
    case 1268:
        name = "`1Splint``";
        break;
    case 1270:
        name = "`9Stitches``";
        break;
    case 4308:
        name = "`4Pins``";
        break;
    case 4310:
        name = "`8Transfusion``";
        break;
    case 4312:
        name = "`6Defibillator``";
        break;
    case 4314:
        name = "`5Clamp``";
        break;
    case 4316:
        name = "`4Ultrasound``";
        break;
    case 4318:
        name = "`7Lab Kit``";
        break;
    case 1296:
        name = "`1Gloves``";
        break;
    default:
        name = "`bid=" + std::to_string(id) + "``";
        break;
    }

    if (content.find("|noflags|" + std::to_string(id) + "|") == std::string::npos) {
        gt::send_log("You ran out of " + name + " tool!");
        id = 4320;
    }
    sel.push_back(std::thread(tool_thread, id, name));
    return;
}
void anti_gravity() {
    GameUpdatePacket packet{ 0 };
    packet.type = PACKET_TILE_CHANGE_REQUEST;
    packet.item_id = 4992;
    packet.int_x = 99;
    packet.int_y = 59;
    g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(GameUpdatePacket));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    auto pos = g_server->m_world.local.pos;

    g_server->enterDoor(true, 99, 59);


    GameUpdatePacket legitpacket{ 0 };
    legitpacket.type = PACKET_STATE;
    legitpacket.item_id = 18;
    legitpacket.int_x = 99;
    legitpacket.int_y = 59;
    legitpacket.vec_x = pos.m_x;
    legitpacket.vec_y = pos.m_y;
    legitpacket.flags = 2592;
    g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&legitpacket, sizeof(GameUpdatePacket));
}
bool itsmod(int netid, std::string growid = "")
{
    if (modas) {
        if (netid == g_server->m_world.local.netid)
            return false;
        else if (growid.find(g_server->m_world.local.name) != std::string::npos)
            return false;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        for (auto g : g_server->m_world.players)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(5));
            std::transform(g.name.begin(), g.name.end(), g.name.begin(), [](unsigned char c) { return std::tolower(c); });
            if (netid == g.netid)
                return false;
            else if (growid.find(g.name) != std::string::npos)
                return false;
        }
        gt::send_log("`2A `#@Moderator `2Joined the World");
        variantlist_t varlist{ "OnAddNotification" };
        varlist[1] = "interface/atomic_button.rttex";
        varlist[2] = "`2A `#@Moderator `2Joined the World";
        varlist[3] = "audio/hub_open.wav";
        varlist[4] = 0;
        g_server->send(true, varlist);
        if (ban_all && exit_world) {
            ban_everyone();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            unaccess();
            exit_pasaulis();

        }

        else if (ban_all)
        {
            ban_everyone();
            unaccess();
        }
        else if (exit_world) {
            exit_pasaulis();
            unaccess();

        }
        return true;
    }
}
bool events::out::worldoptions(std::string option)
{
    std::string username = "all";
    for (auto& player : g_server->m_world.players) {
        auto name_2 = player.name.substr(2); //remove color
        std::transform(name_2.begin(), name_2.end(), name_2.begin(), ::tolower);
        if (name_2.find(username)) {
            auto& bruh = g_server->m_world.local;
            if (option == "pull")
            {
                string plyr = player.name.substr(2).substr(0, player.name.length() - 4);
                if (plyr != bruh.name.substr(2).substr(0, player.name.length() - 4))
                {
                    g_server->send(false, "action|input\n|text|/pull " + plyr);
                }
            }
            if (option == "kick")
            {
                string plyr = player.name.substr(2).substr(0, player.name.length() - 4);
                if (plyr != bruh.name.substr(2).substr(0, player.name.length() - 4))
                {
                    g_server->send(false, "action|input\n|text|/kick " + plyr);

                }
            }
            if (option == "ban")
            {
                string plyr = player.name.substr(2).substr(0, player.name.length() - 4);
                if (plyr != bruh.name.substr(2).substr(0, player.name.length() - 4))
                {
                    g_server->send(false, "action|input\n|text|/ban " + plyr);

                }
            }
        }
    }

    return true;
}
void fast_shop(int aga) {
    for (int i = 0; i < aga; i++) {
        g_server->send(false, "action|buy\nitem|" + lastshop, 2);
    }
    shopmode = false;
    gt::send_log(" bought " + to_string(aga) + " " + lastshop);
}

bool events::out::generictext(std::string packet) {

    if (iswear) send_vset();
    // PRINTS("Generic text: %s\n", packet.c_str());
    auto& world = g_server->m_world;
    rtvar var = rtvar::parse(packet);
    if (!var.valid())
        return false;
    /*if (iswear) {
        int skincolor = 1685231359;
        variantlist_t liste{ "OnSetClothing" };
        liste[1] = vector3_t{ hair,  shirt,  pants };
        liste[2] = vector3_t{ shoe,  face,  hand };
        liste[3] = vector3_t{ back,  mask,  neck };
        liste[4] = skincolor;
        liste[5] = vector3_t{ ances , 1.f, 0.f };

        g_server->send(true, liste, g_server->m_world.local.netid, -1);
        g_server->sendState(g_server->m_world.local.netid);
    }*/
    if (packet.find("dicespeed|") != -1) {
        try
        {
            std::string aaa = packet.substr(packet.find("eed|") + 4, packet.size());
            std::string number = aaa.c_str();
           
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");
        }
    }
    if (packet.find("autobgl|") != -1) {
        try
        {
            std::string aaa = packet.substr(packet.find("bgl|") + 4, packet.size());
            std::string number = aaa.c_str();
            autobgl = stoi(number);
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");
        }
    }
    if (packet.find("buttonClicked|iso11pul1") != -1) {
        mode = "`5Pull"; //bannj
        return true;
    }
    if (packet.find("buttonClicked|iso11pul2") != -1) {
        hostermode = !hostermode; //bannj
        return true;
    }
    if (packet.find("growscan_dialog") != -1) {

        return true;
    }
    if (packet.find("buttonClicked|bannj") != -1) {
        mode = "`4Ban";
        return true;
    }
    if (packet.find("buttonClicked|kicjlabas") != -1) {
        mode = "`4Kick";
        return true;
    }

    if (packet.find("autoacc|") != -1)
    {
        try
        {
            std::string aaa = packet.substr(packet.find("acc|") + 4, packet.size());
            std::string number = aaa.c_str();
            autoacc = stoi(number);
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");
        }
    }
    if (packet.find("autobgl|") != -1) {
        try
        {
            std::string aaa = packet.substr(packet.find("bgl|") + 4, packet.size());
            std::string number = aaa.c_str();
            autobgl = stoi(number);
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");
        }
    }
    if (packet.find("ac_page") != -1) {
        if (packet.find("ac_enable|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("ble|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                gt::autocollect = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("ac_range") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("nge|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                gt::ac_range = std::stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        return true;
    }
    if (packet.find("mod_settings_spare") != -1) {
        if (packet.find("leaveworld|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("rld|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                exit_world = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("isjunkvisusnx|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("snx|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                ban_all = stoi(number);
            }
            catch (exception a)
            {
                std::cout << "ERROR: " << a.what() << '\n';
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        return true;
    }
    if (packet.find("buttonClicked|title") != -1) {
        Dialog title;
        title.addLabelWithIcon("Title", 11816, LABEL_BIG);

        title.addCheckbox("drtitle", "Dr.", drtitle);
        title.addCheckbox("maxlevel", "Level 125", maxlevel);
        title.addCheckbox("legend", "of legend", legend);
        title.addCheckbox("g4g", "G4G Title", g4g);

        title.addSpacer(SPACER_SMALL);
        title.endDialog("titledialog", "Okay", "Cancel");
        variantlist_t packet{ "OnDialogRequest" };
        packet[1] = title.finishDialog();
        g_server->send(true, packet);

    }
    if (packet.find("maxlevel|") != -1) {
        string istoggled = packet.substr(packet.find("vel|") + 4, 1);
        cout << istoggled;
        if (istoggled == "1") {
            maxlevel = true;
        }
        else {
            maxlevel = false;
        }
    }
    if (packet.find("drtitle|") != -1) {
        string istoggled = packet.substr(packet.find("tle|") + 4, 1);
        cout << istoggled;
        if (istoggled == "1") {
            string name = "`4Dr." + g_server->m_world.local.name + "`4";
            variantlist_t va{ "OnNameChanged" };
            va[1] = name;
            g_server->send(true, va, world.local.netid, -1);
            drtitle = true;
        }
        else {
            drtitle = false;
        }
    }
    if (packet.find("legend|") != -1) {
        string istoggled = packet.substr(packet.find("end|") + 4, 1);
        cout << istoggled;
        if (istoggled == "1") {
            string name = "``" + g_server->m_world.local.name + " of Legend``";
            variantlist_t va{ "OnNameChanged" };
            va[1] = name;
            g_server->send(true, va, world.local.netid, -1);
            legend = true;
        }
        else {
            legend = false;
        }
    }

    if (packet.find("g4g|") != -1) {
        string istoggled = packet.substr(packet.find("g4g|") + 4, 1);
        if (istoggled == "1") {
            g4g = true;
        }
        else {
            g4g = false;
        }
        return true;
    }
    if (packet.find("buttonClicked|wblock") != -1) {
        auto round = [](double n) {
            return n - floor(n) >= 0.5 ? ceil(n) : floor(n);
        };

        std::map<int, std::map<std::string, int>> store1;

        for (auto tile : g_server->m_world.tiles) {
            int id = tile.second.header.foreground;
            if (id != 0) {
                if (store1[tile.second.header.foreground].empty()) {
                    store1[tile.second.header.foreground] = { {"id", tile.second.header.foreground}, {"qty", 1} };
                }
                else {
                    store1[tile.second.header.foreground]["qty"] += 1;
                }
                if (store1[tile.second.header.background].empty()) {
                    store1[tile.second.header.background] = { {"id", tile.second.header.background}, {"qty", 1} };
                }
                else {
                    store1[tile.second.header.background]["qty"] += 1;
                }
            }
        }

        std::string placed_items = "add_spacer|small|";
        for (auto& tile : store1) {
            int count = round(tile.second["qty"]);
            int idplaced = floor(tile.second["id"]);
            placed_items += "\nadd_label_with_icon|small|`0" + std::to_string(count) + "``|left|" + std::to_string(idplaced);
        }

        std::string paket =
            "set_default_color|`o\nadd_label_with_icon|big|`0World blocks: `0``|left|170\n" + placed_items + "\nadd_quick_exit";
        variantlist_t liste{ "OnDialogRequest" };
        liste[1] = paket;
        g_server->send(true, liste);
        return true;
    }
    if (packet.find("buttonClicked|wfloat") != -1) {
        std::string droppedshit = "add_spacer|small|\nadd_label_with_icon_button_list|small|`w%s : %s|left|findObject_|itemID_itemAmount|";

        int itemid;
        int count = 0;
        std::vector<std::pair<int, int>> ditems;
        std::string itemlist = "";
        auto& objMap = g_server->m_world;

        if (objMap.connected) {
            std::unordered_map<uint32_t, DroppedItem> updatedObjects;

            for (auto& object : objMap.objects) {
                bool found = false;
                for (int i = 0; i < ditems.size(); i++) {
                    if (ditems[i].first == object.second.itemID) {
                        ditems[i].second += object.second.count;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    ditems.push_back(make_pair(object.second.itemID, object.second.count));
                }
                else {
                    updatedObjects[object.first], object.second;
                }
            }
            objMap.objects = updatedObjects;

            if (ditems.empty()) {
                gt::send_log("No dropped items found.");
                return false;
            }

            for (int i = 0; i < ditems.size(); i++) {
                itemlist += std::to_string(ditems[i].first) + "," + std::to_string(ditems[i].second) + ",";
            }
            std::string paket = "set_default_color|`o\nadd_label_with_icon|big|`wFloating Items``|left|6016|\n" + droppedshit + itemlist.substr(0, itemlist.size() - 1) + "\nadd_quick_exit|dropped||Back|\n";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }
        else {
            gt::send_log("Not connected to the world.");
            return false;
        }
    }
    if (packet.find("buttonClicked|kadaryt") != -1) {
        try {
            Dialog a;
            a.addLabelWithIcon("Auto Mod Detect Settings", 278, LABEL_BIG);
            a.addTextBox("`9When `#@Moderator`9 Joins The World You will:");
            a.addCheckbox("leaveworld", "`9Exit World", exit_world);
            a.addCheckbox("isjunkvisusnx", "`9Ban Everyone in World", ban_all);
            a.endDialog("mod_settings_spare", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);
        }
        catch (exception a) {
            gt::send_log("`4Critical Error: `2override detected");
        }
        return true;
    }
    if (packet.find("buttonClicked|save1") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ofstream vw;
            vw.open("clothes.txt");
            vw << clothes;
            vw.close();
        }
        vr >> clothes;
        vr.close();
        return true;
    }
    if (packet.find("buttonClicked|save2") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ofstream vw;
            vw.open("clothes2.txt");
            vw << clothes2;
            vw.close();
        }
        vr >> clothes2;
        vr.close();
        return true;
    }
    if (packet.find("buttonClicked|save3") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ofstream vw;
            vw.open("clothes3.txt");
            vw << clothes3;
            vw.close();
        }
        vr >> clothes3;
        vr.close();
        return true;
    }
    if (packet.find("buttonClicked|load1") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ifstream vw;
            vw.open("clothes.txt");
            vw; load1;
            vw.close();
        }
        vr; load1;
        vr.close();
        return true;
    }
    if (packet.find("buttonClicked|load2") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ifstream vw;
            vw.open("clothes2.txt");
            vw; load2;
            vw.close();
        }
        vr; load2;
        vr.close();
        return true;
    }
    if (packet.find("buttonClicked|load3") != -1)
    {
        std::ifstream vr;
        if (!vr) {
            std::ifstream vw;
            vw.open("clothes3.txt");
            vw; load3;
            vw.close();
        }
        vr; load3;
        vr.close();
        return true;
    }
    if (packet.find("saveworld|") != -1) {
        try
        {
            std::string aaa = packet.substr(packet.find("rld|") + 4, packet.size());
            while (!aaa.empty() && isspace(aaa[aaa.size() - 1]))
                aaa.erase(aaa.end() - (76 - 0x4B));
            events::out::saveworld = aaa;
        }
        catch (exception a)
        {

        }
    }
    if (packet.find("speed_page") != -1) {
        try {
            if (packet.find("ed_x|") != -1) {
                std::string aaa = packet.substr(packet.find("d_x|") + 4, packet.size());
                std::string number = aaa.c_str();
                // cout << number << endl;
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                speed_x = stof(number);
                g_server->sendState(world.local.netid);
            }
            if (packet.find("ed_y|") != -1) {
                std::string aaa = packet.substr(packet.find("d_y|") + 4, packet.size());
                std::string number = aaa.c_str();
                //cout << number << endl;
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                speed_y = stof(number);
                g_server->sendState(world.local.netid);
            }

        }
        catch (exception a) {
            std::cout << "error?";
            std::cout << a.what();
        }
        return true;
    }
    if (packet.find("spam_text") != -1) {
        try {
            if (packet.find("c_text|") != -1) {
                std::string aaa = packet.substr(packet.find("ext|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                enabled_color = stoi(number);
            }
            if (packet.find("auto_enable|") != -1) {
                std::string aaa = packet.substr(packet.find("ble|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                son = stoi(number);
            }
            if (packet.find("spam_msg|") != -1) {
                std::string msg = packet.substr(packet.find("spam_msg|") + 9, packet.length() - packet.find("spam_msg") - 1);
                aspam = msg;
            }
            if (packet.find("delay_msg|") != -1) {
                std::string msg = packet.substr(packet.find("delay_msg|") + 10, packet.length() - packet.find("delay_msg") - 1);
                delay = stoi(msg);
            }

        }
        catch (exception a) {
            std::cout << "error?";
            std::cout << a.what();
        }
        return true;
    }
    /*if (packet.find("spam_page") != -1) {
        if (packet.find("coloredtext") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("ext|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                enabled_color= stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        delay = std::stoi(packet.substr(packet.find("message_8|") + 10, packet.length() - packet.find("message_8|") - 1));
        aspam = std::stoi(packet.substr(packet.find("message_9|") + 10, packet.length() - packet.find("message_9|") - 1));
        return true;
    }*/
    if (packet.find("find_dialog") != -1) {
        if (packet.find("buttonClicked|spare_btn_") != -1) {
            std::string iID = packet.substr(packet.find("buttonClicked|spare_btn_") + 24, packet.length() - packet.find("buttonClicked|spare_btn_") - 1);
            gameupdatepacket_t xp{ 0 };
            xp.m_type = PACKET_MODIFY_ITEM_INVENTORY;
            xp.m_count = 0;
            xp.m_int_data = atoi(iID.c_str());
            g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&xp, sizeof(gameupdatepacket_t));
            auto item = items[atoi(iID.c_str())];
            gt::send_log("`9succesfully gave `#" + item.name);
        }
        if (packet.find("vclothes") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("hes|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                iswear = stoi(number);
                if (iswear == true) {

                }
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        return true;
    }
    if (packet.find("banby_name") != -1) {
        try {
            int banbyname = std::stoi(packet.substr(packet.find("pullban_1|") + 10, packet.length() - packet.find("pullban_1|") - 1));
            std::string autobanas = packet.substr(packet.find("pullban_2|") + 10, packet.length() - packet.find("pullban_2|") - 1);
            std::string basik = " ";
            vardasban = basik + autobanas;
            gt::send_log("`9Successfully added to Autoban List");
            if (banbyname > 0) {
                banbynames = true;
            }
            else {
                banbynames = false;
            }
        }
        catch (std::exception) {
            gt::send_log("Critical Error : Something went wrong. Try Again Later");
        }
        return true;
    }
    if (packet.find("pullby_name") != -1) {
        try {
            int pullbyname = std::stoi(packet.substr(packet.find("pullnam_1|") + 10, packet.length() - packet.find("message_1|") - 1));
            std::string autopulas = packet.substr(packet.find("pullnam_2|") + 10, packet.length() - packet.find("message_2|") - 1);
            std::string basik = " ";
            vardaspull = basik + autopulas;
            gt::send_log("`9Successfully added to AutoPull List");
            if (pullbyname > 0) {
                pullbynames = true;
            }
            else {
                pullbynames = false;
            }
        }
        catch (std::exception) {
            gt::send_log("Critical Error : Something went wrong. Try Again Later");
        }
        return true;
    }
    if (packet.find("auto_dialog") != -1) {
        try {
            int autoban = std::stoi(packet.substr(packet.find("pullnam_3|") + 10, packet.length() - packet.find("pullnam_3|") - 1));
            int autopulis = std::stoi(packet.substr(packet.find("pullnam_4|") + 10, packet.length() - packet.find("pullnam_4|") - 1));
            if (autoban > 0) {
                enter_ban = true;
            }
            else {
                enter_ban = false;
            }
            if (autopulis > 0) {
                enter_pull = true;
            }
            else {
                enter_pull = false;
            }
        }
        catch (std::exception) {
            gt::send_log("Critical Error : Something Error. Try Again Later");
        }
        if (packet.find("buttonClicked|load1") != -0) {
            std::ifstream vr;
            try
            {
                std::ofstream vw;
                vw.open("clothes.txt");
                vw << clothes;
                vw.close();
            }

            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
            return true;
        }
        if (packet.find("buttonClicked|load2") != -0) {
            std::ifstream vr;
            try
            {
                std::ofstream vw;
                vw.open("clothes2.txt");
                vw << clothes2;
                vw.close();
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
            return true;
        }
        if (packet.find("buttonClicked|load1") != -0) {
            std::ifstream vr;
            try
            {
                std::ofstream vw;
                vw.open("clothes3.txt");
                vw << clothes3;
                vw.close();
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
            return true;
        }

        if (packet.find("buttonClicked|autopuli") != -1) {
            if (pullbynames == true) {
                pname = "1";
            }
            else {
                pname = "0";
            }
            std::string listaspull;
            //if (!vardaspull.empty())  listaspull = "\nadd_textbox|`cName: "+vardaspull+"|left|2480|";
            std::string pull;
            pull =
                "add_label_with_icon|big|`2AutoPull Page|left|2246|"
                "\nadd_textbox|`9Name has to be fully written, for autopull to work.|left|2480|"
                "\nadd_textbox|`9Name has be to atleast 3 letters long & without spaces|left|2480|"
                //"\nadd_textbox|`cName: " + (vardaspull.empty() ? "`4Empty``" : vardaspull) + "|left|2480|"
                "\nadd_checkbox|pullnam_1|`2Enable Auto Pull|" +
                pname +
                "|"
                "\nadd_text_input|pullnam_2|Name||20|"
                "\nend_dialog|pullby_name|Cancel|okay|";
            variantlist_t pot{ "OnDialogRequest" };
            pot[1] = pull;
            g_server->send(true, pot);
            return true;
        }
        if (packet.find("buttonClicked|autobani") != -1) {
            if (banbynames == true) {
                bname = "1";
            }
            else {
                bname = "0";
            }
            std::string listasban;
            // if (!vardasban.empty()) listasban = "\nadd_textbox|`cName: " + vardasban + "|left|2480|";
            std::string ban;
            ban =
                "add_label_with_icon|big|`2AutoBan Page|left|2242|"
                "\nadd_textbox|`9Name has to be fully written, for autoban to work.|left|2480|"
                "\nadd_textbox|`9Name has be to atleast 3 letters long & without spaces|left|2480|"
                "//\n" + listasban + ""
                "\nadd_checkbox|pullban_1|`4Enable Auto ban|" +
                bname +
                "|"
                "\nadd_text_input|pullban_2|Name||20|"
                "\nend_dialog|banby_name|Cancel|okay|";
            variantlist_t pot{ "OnDialogRequest" };
            pot[1] = ban;
            g_server->send(true, pot);
            return true;
        }
        return true;
    }
    if (packet.find("wrenchpull|") != -1) {
        try {
            std::string aaa = packet.substr(packet.find("ull|") + 4, packet.size());
            std::string number = aaa.c_str();
            while (!number.empty() && isspace(number[number.size() - 1]))
                number.erase(number.end() - (76 - 0x4B));
            wrench = stoi(number);
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
        return true;
    }
    if (packet.find("buttonClicked|hotkeys1") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys1 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys2") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys2 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys3") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys3 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys4") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys4 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }

    if (packet.find("buttonClicked|hotkeys5") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys5 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys6") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys6 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys7") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys7 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys8") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys8 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeys9") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys9 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeysa10") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys10 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeyss11") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());

            hotkeys11 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("buttonClicked|hotkeysq12") != -1) {
        try
        {
            std::string number = packet.substr(packet.find("message_9|") + 10, packet.size());
            hotkeys12 = number;
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
    }
    if (packet.find("title_page") != -1) {

        if (packet.find("legend") != -1) {

            try
            {
                std::string aaa = packet.substr(packet.find("end|") + 4, packet.size());
                std::string number = aaa.c_str();
                legend = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("mentor") != -1) {

            try
            {

                std::string aaa = packet.substr(packet.find("tor|") + 4, packet.size());
                std::string number = aaa.c_str();
                mentor = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("caitriona") != -1) {

            try
            {
                std::string aaa = packet.substr(packet.find("ona|") + 4, packet.size());
                std::string number = aaa.c_str();
                caitriona = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("g4g") != -1) {

            try
            {
                std::string aaa = packet.substr(packet.find("g4g|") + 4, packet.size());
                std::string number = aaa.c_str();
                g4g = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
    }
    if (packet.find("options_page") != -1) {

        if (packet.find("fastdrop|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rop|") + 4, packet.size());
                std::string number = aaa.c_str();
                fastdrop = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("fastdrjp|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rjp|") + 4, packet.size());
                std::string number = aaa.c_str();
                gt::ghost = stoi(number);
                g_server->sendState(world.local.netid);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("fastdrbp|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rbp|") + 4, packet.size());
                std::string number = aaa.c_str();
                autoacc = stoi(number);

            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("fasttrap|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rap|") + 4, packet.size());
                std::string number = aaa.c_str();
                fasttrash = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("fasttrkp|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rkp|") + 4, packet.size());
                std::string number = aaa.c_str();
                ssup = stoi(number);
                g_server->sendState(world.local.netid);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("fasttrqp|") != -1) {
            try
            {
                std::string aaa = packet.substr(packet.find("rqp|") + 4, packet.size());
                std::string number = aaa.c_str();
                antigravity = stoi(number);
                GameUpdatePacket packet{ 0 };
                packet.type = PACKET_TILE_CHANGE_REQUEST;
                packet.item_id = 4992;
                packet.int_x = 99;
                packet.int_y = 59;
                g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(GameUpdatePacket));
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                auto pos = g_server->m_world.local.pos;

                g_server->enterDoor(true, 99, 59);


                GameUpdatePacket legitpacket{ 0 };
                legitpacket.type = PACKET_STATE;
                legitpacket.item_id = 18;
                legitpacket.int_x = 99;
                legitpacket.int_y = 59;
                legitpacket.vec_x = pos.m_x;
                legitpacket.vec_y = pos.m_y;
                legitpacket.flags = 2592;
                g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&legitpacket, sizeof(GameUpdatePacket));


            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }

        if (packet.find("enablemod|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("mod|") + 4, packet.size());
                std::string number = aaa.c_str();
                while (!number.empty() && isspace(number[number.size() - 1]))
                    number.erase(number.end() - (76 - 0x4B));
                modas = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("remes|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("mes|") + 4, packet.size());
                std::string number = aaa.c_str();
                remee = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("qqs|") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("qqs|") + 4, packet.size());
                std::string number = aaa.c_str();
                qqe = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("AutoBglG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("autobglG|") + 4, packet.size());
                std::string number = aaa.c_str();
                autobgl = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("gasspullG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("gasspullG|") + 4, packet.size());
                std::string number = aaa.c_str();
                gaspull = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("LegendG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("legendG|") + 4, packet.size());
                std::string number = aaa.c_str();
                legend = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("bluenameG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("bluenameG|") + 4, packet.size());
                std::string number = aaa.c_str();
                maxlevel = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("g4gG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("g4gG|") + 4, packet.size());
                std::string number = aaa.c_str();
                g4g = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("mentorG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("mentorG|") + 4, packet.size());
                std::string number = aaa.c_str();
                mentor = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("sethG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("sethG|") + 4, packet.size());
                std::string number = aaa.c_str();
                seth = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }
        if (packet.find("caitrionaG") != -1) {
            try {
                std::string aaa = packet.substr(packet.find("caitrionaG|") + 4, packet.size());
                std::string number = aaa.c_str();
                caitriona = stoi(number);
            }
            catch (exception a)
            {
                gt::send_log("`4Critical Error: `2override detected");

            }
        }

        return true;
    }
    if (packet.find("buttonClicked|killall") != -1) {
        worldoptions("kick");
        return true;
    }
    if (packet.find("buttonClicked|banall") != -1) {
        worldoptions("ban");
        return true;
    }
    if (packet.find("buttonClicked|pullall") != -1) {
        worldoptions("pull");
        return true;
    }
    if (packet.find("notaxmode") != -1)
    {
        std::string x = packet.substr(packet.find("mpx|") + 4, packet.size());
        std::string y = packet.substr(packet.find("mpy|") + 4, packet.size());
        try {
            std::string aaa = packet.substr(packet.find("ode|") + 4, packet.size());
            std::string number = aaa.c_str();
            while (!number.empty() && isspace(number[number.size() - 1]))
                number.erase(number.end() - (76 - 0x4B));
            notax_mode = stoi(number);
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
        notaxx = stoi(x.c_str());
        notaxy = stoi(y.c_str());
        return true;
    }
    if (packet.find("farmid") != -1)
    {
        std::string x = packet.substr(packet.find("mid|") + 4, packet.size());
        farmid = stoi(x.c_str());
        std::string legitz = packet.substr(packet.find("des|") + 4, packet.size()); //umb
        farmauto = stoi(legitz.c_str());
        return true;
    }
    if (packet.find("roulettex") != -1)
    {
        try {
            std::string color = packet.substr(packet.find("color|") + 6, packet.size());
            std::string sayi = packet.substr(packet.find("number|") + 7, packet.size());
            std::string x = packet.substr(packet.find("tex|") + 4, packet.size());
            std::string y = packet.substr(packet.find("tey|") + 4, packet.size());
            std::string delays = packet.substr(packet.find("lay|") + 4, packet.size());
            std::string remzq = packet.substr(packet.find("rmq|") + 4, packet.size()); //umb
            type = stoi(remzq);
            roulettex = stoi(x.c_str());
            roulettey = stoi(y.c_str());
            typenumber = stoi(sayi.c_str());
            color_type = stoi(color.c_str());
            type_delay = stoi(delays.c_str());
            return true;
        }
        catch (exception a)
        {
            gt::send_log("`4Critical Error: `2override detected");

        }
        return true;
    }
    if (packet.find("lampx") != -1)
    {
        std::string px2 = packet.substr(packet.find("chx|") + 4, packet.size());
        std::string py2 = packet.substr(packet.find("chy|") + 4, packet.size());
        std::string x = packet.substr(packet.find("mpx|") + 4, packet.size());
        std::string y = packet.substr(packet.find("mpy|") + 4, packet.size());
        std::string x2 = packet.substr(packet.find("mpx2|") + 5, packet.size());
        std::string y2 = packet.substr(packet.find("mpy2|") + 5, packet.size());
        std::string sayi = packet.substr(packet.find("umb|") + 4, packet.size()); //umb
        std::string sayi2 = packet.substr(packet.find("umd|") + 4, packet.size()); //
        std::string sayi3 = packet.substr(packet.find("umk|") + 4, packet.size()); //
        std::string legitz = packet.substr(packet.find("itp|") + 4, packet.size()); //umb
        std::string modez = packet.substr(packet.find("ode|") + 4, packet.size()); //umb

        std::string remzes = packet.substr(packet.find("rmk|") + 4, packet.size()); //umb
        csn_punch = stoi(remzes);
        std::string remze = packet.substr(packet.find("rme|") + 4, packet.size()); //umb
        reme = stoi(remze);

        std::string remzq = packet.substr(packet.find("rmq|") + 4, packet.size()); //umb
        qeme = stoi(remzq);

        lampx = stoi(x.c_str());
        lampy = stoi(y.c_str());
        lampx2 = stoi(x2.c_str());
        lampy2 = stoi(y2.c_str());
        punchx = stoi(px2.c_str());
        punchy = stoi(py2.c_str());
        selectednumber = stoi(sayi.c_str());
        reme_delay = stoi(sayi2.c_str());
        punch_delay = stoi(sayi3.c_str());
        legit = stoi(legitz);
        rmode = stoi(modez);
        return true;
    }
    if (packet.find("buttonClicked|ubaworld") != -1) {
        g_server->send(false, "action|input\n|text|/uba");
        return true;
    }
    if (packet.find("action|res") != -1) {
        g_server->send(false, "action|input\n|text|/respawn");
        return true;
    }
    if (wrench == true) {
        if (hostermode == true) {
            if (packet.find("action|wrench") != -1) {
                if (GetAsyncKeyState(0x01)) {
                    g_server->send(false, packet);

                    std::string str = packet.substr(packet.find("netid|") + 6, packet.length() - packet.find("netid|") - 1);
                    std::string gta5 = str.substr(0, str.find("|"));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + gta5 + "|\nnetID|" + gta5 + "|\nbuttonClicked|pull");
                }
                else  if (GetAsyncKeyState(0x02)) {
                    g_server->send(false, packet);

                    std::string str = packet.substr(packet.find("netid|") + 6, packet.length() - packet.find("netid|") - 1);
                    std::string gta5 = str.substr(0, str.find("|"));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + gta5 + "|\nnetID|" + gta5 + "|\nbuttonClicked|kick");
                }
                std::string str = packet.substr(packet.find("netid|") + 6, packet.length() - packet.find("netid|") - 1);
                std::string gta5 = str.substr(0, str.find("|"));
                variantlist_t varlist{ "OnTextOverlay" };
                varlist[1] = "Successfuly " + mode + "`` netID: " + gta5;
                g_server->send(true, varlist);
                return true;
            }
        }
        else {
            if (packet.find("action|wrench") != -1) {
                g_server->send(false, packet);

                std::string str = packet.substr(packet.find("netid|") + 6, packet.length() - packet.find("netid|") - 1);
                std::string gta5 = str.substr(0, str.find("|"));
                if (mode == "`5Pull") {
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + gta5 + "|\nnetID|" + gta5 + "|\nbuttonClicked|pull");
                }
                if (mode == "`4Kick") {
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + gta5 + "|\nnetID|" + gta5 + "|\nbuttonClicked|kick");
                }
                if (mode == "`4Ban") {
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + gta5 + "|\nnetID|" + gta5 + "|\nbuttonClicked|worldban");
                }
                variantlist_t varlist{ "OnTextOverlay" };
                varlist[1] = "Successfuly " + mode + "`` netID: " + gta5;
                g_server->send(true, varlist);
                return true;
            }
        }
    }
    /*if (GetAsyncKeyState(VK_F1) & 1)
    {
        son = !son;
        std::thread([&]() {
            const string colored_text_array[10] = { "`2", "`3", "`4", "`#", "`9", "`8", "`c", "`6", "`^" , "`b" };
            while (son) {
                string send_ = colored_text_array[rand() % 10];
                g_server->send(false, "action|input\n|text|" + send_ + aspam);
                std::this_thread::sleep_for(std::chrono::seconds(4));
            }
            }).detach();
            //return true;
    }*/
    if (var.get(0).m_key == "action" && var.get(0).m_value == "input") {
        if (var.size() < 2)
            return false;
        if (var.get(1).m_values.size() < 2)
            return false;

        if (!world.connected)
            return false;
        auto chat = var.get(1).m_values[1];
        if (find_command(chat, "seth") || find_command(chat, "Seth") || find_command(chat, "SETH")) {
            auto& visuals = g_server->m_world.local;
            variantlist_t va{ "OnNameChanged" };
            va[1] = "`8@Seth";
            g_server->send(true, va, world.local.netid, -1);
            gt::send_log("name set to: `8@Seth");
            return true;
        }
        if (find_command(chat, "caitriona") || find_command(chat, "Caitriona") || find_command(chat, "CAITRIONA")) {
            auto& visuals = g_server->m_world.local;
            variantlist_t va{ "OnNameChanged" };
            va[1] = "`#@Caitriona";
            g_server->send(true, va, world.local.netid, -1);
            gt::send_log("name set to: `#@Caitriona");
            return true;
        }
        if (find_command(chat, "Doctor") || find_command(chat, "doctor") || find_command(chat, "DOCTOR")) {
            auto& visuals = g_server->m_world.local;
            variantlist_t va{ "OnNameChanged" };
            va[1] = "`4Dr." "`4" + visuals.name + "`4";
            g_server->send(true, va, world.local.netid, -1);
            gt::send_log("title set to: " + visuals.name + " Dr.");
            return true;
        }
        if (find_command(chat, "legend") || find_command(chat, "Legend") || find_command(chat, "LEGEND")) {
            auto& visuals = g_server->m_world.local;
            variantlist_t va{ "OnNameChanged" };
            va[1] = "``" + visuals.name + " of Legend``";
            g_server->send(true, va, world.local.netid, -1);
            gt::send_log("name set to: " + visuals.name + " of Legend");
            return true;
        }
        else if (find_command(chat, "mentor") || find_command(chat, "Mentor") || find_command(chat, "MENTOR")) {
            std::string mn = "|showGuild|master";

            variantlist_t mentor{ "OnCountryState" };
            mentor[1] = mn.c_str();
            g_server->send(true, mentor, g_server->m_world.local.netid, -1);
            return true;
        }

        else if (find_command(chat, "maxlevel") || find_command(chat, "MaxLevel") || find_command(chat, "Maxlevel") || find_command(chat, "MAXLEVEL")) {
            std::string packet125level = "us|showGuild|maxLevel";

            variantlist_t packet123{ "OnCountryState" };
            packet123[1] = packet125level.c_str();
            g_server->send(true, packet123, g_server->m_world.local.netid, -1);
            return true;
        }
        else if (find_command(chat, "g4g") || find_command(chat, "G4G") || find_command(chat, "G4g")) {
            std::string packet125level = "us|showGuild|donor";

            variantlist_t packet123{ "OnCountryState" };
            packet123[1] = packet125level.c_str();
            g_server->send(true, packet123, g_server->m_world.local.netid, -1);
            return true;
            //visuals end
        }
        if (find_command(chat, "name ") || find_command(chat, "Name ") || find_command(chat, "NAME"))
        {
            std::string name = "``" + chat.substr(6) + "``";
            variantlist_t va{ "OnNameChanged" };
            va[1] = name;
            g_server->send(true, va, world.local.netid, -1);
            gt::send_log("name set to: " + name);
            return true;
        }
        else if (find_command(chat, "flag ") || find_command(chat, "Flag ") || find_command(chat, "FLAG ")) {
            gt::flag = chat.substr(6);
            variantlist_t varlist{ "OnAddNotification" };
            varlist[1] = 0;
            varlist[2] = "Disconnecting Due to Flag Change";
            varlist[3] = 0;
            varlist[4] = 0;
            g_server->send(true, varlist);
            g_server->disconnectsr(true);
            return true;
        }
        else if (find_command(chat, "res") || find_command(chat, "Res") || find_command(chat, "RES")) {
            if (packet.find("action|res") != -1) {
                g_server->send(false, "action|input\n|text|/respawn");
                return true;
            }
            return true;
        }
        else if (find_command(chat, "countrylist") || find_command(chat, "clist") || find_command(chat, "Countrylist") || find_command(chat, "CountryList") || find_command(chat, "COUNTRYLIST") || find_command(chat, "Clist") || find_command(chat, "CLIST") || find_command(chat, "CList")) {
            std::string paket;
            paket =
                "\nadd_label_with_icon|big|Country List|left|3394|"
                "\nadd_spacer|small"
                "\nadd_textbox|`clt: `#Lithuania|left|2480|"
                "\nadd_textbox|`ctr: `#Turkey|left|2480|"
                "\nadd_textbox|`cen: `#USA|left|2480|"
                "\nadd_textbox|`ckr: `#Korean|left|2480|"
                "\nadd_textbox|`cid: `#Indonesia|left|2480|"
                "\nadd_textbox|`caf: `#Afghanistan|left|2480|"
                "\nadd_textbox|`cal: `#Albania|left|2480|"
                "\nadd_textbox|`cdz: `#Algeria|left|2480|"
                "\nadd_textbox|`cas: `#American Samoa|left|2480|"
                "\nadd_textbox|`cad: `#Andorra|left|2480|"
                "\nadd_textbox|`cao: `#Angola|left|2480|"
                "\nadd_textbox|`cai: `#Anguilla|left|2480|"
                "\nadd_textbox|`caq: `#Antarctica|left|2480|"
                "\nadd_textbox|`cag: `#Antigua and Barbuda|left|2480|"
                "\nadd_textbox|`car: `#Argentina|left|2480|"
                "\nadd_textbox|`cam: `#Armenia|left|2480|"
                "\nadd_textbox|`cth: `#Thailand|left|2480|"
                "\nadd_textbox|`ces: `#Spain|left|2480|"
                "\nadd_textbox|`cso: `#Somalia|left|2480|"
                "\nadd_textbox|`cse: `#Sweden|left|2480|"
                "\nadd_textbox|`cmm: `#Myanmar|left|2480|"
                "\nadd_quick_exit|"
                "\nend_dialog|end|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "autosurg") || find_command(chat, "AUTOSURG") || find_command(chat, "AutoSurg") || find_command(chat, "Autosurg")) {
            auto_surg = !auto_surg;
            if (auto_surg)
                gt::send_log("`9Auto Surgery `2enabled");
            else
                gt::send_log("`9Auto Surgery `4disabled");

            return true;
        }
        else if (find_command(chat, "keep") || find_command(chat, "KEEP") || find_command(chat, "Keep")) {
            save_details();
            gt::send_log("`2Keeped proxy details.");

            return true;
        }
        else if (find_command(chat, "tp ")) {
            std::string name = chat.substr(4);
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);
            for (auto& player : g_server->m_world.players) {
                auto name_2 = player.name.substr(2); //remove color
                std::transform(name_2.begin(), name_2.end(), name_2.begin(), ::tolower);
                if (name_2.find(name) == 0) {
                    gt::send_log("Teleporting to " + player.name);
                    variantlist_t varlist{ "OnSetPos" };
                    varlist[1] = player.pos;
                    g_server->m_world.local.pos = player.pos;
                    g_server->send(true, varlist, g_server->m_world.local.netid, -1);
                    break;
                }
            }
            return true;
        }
        else if (find_command(chat, "save")) {
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("gaspull.txt");
                vw << gaspull;
                vw.close();
            }
            vr >> gaspull;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("gaspull.txt");
                vw << gaspull;
                vw.close();
            }
            vr >> gaspull;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("cntr.txt");
                vw << gt::flag;
                vw.close();
            }
            vr >> gt::flag;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("fasttrash.txt");
                vw << fasttrash;
                vw.close();
            }
            vr >> fasttrash;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("autoacc.txt");
                vw << autoacc;
                vw.close();
            }
            vr >> autoacc;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("wrench.txt");
                vw << wrench;
                vw.close();
            }
            vr >> wrench;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("fdrop.txt");
                vw << fastdrop;
                vw.close();
            }
            vr >> fastdrop;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("realfake.txt");
                vw << antigravity;
                vw.close();
            }
            vr >> antigravity;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("spamtxt.txt");
                vw << aspam;
                vw.close();
            }
            vr >> aspam;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("clothes.txt");
                vw << clothes;
                vw.close();
            }
            vr >> clothes;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("clothes2.txt");
                vw << clothes2;
                vw.close();
            }
            vr >> clothes2;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("clothes3.txt");
                vw << clothes3;
                vw.close();
            }
            vr >> clothes3;
            vr.close();
            gt::send_log("`9Successfully saved all settings/commands");
            return true;
        }

        else if (find_command(chat, "logs")) {
            Dialog a;
            a.addLabelWithIcon("Proxy Logs", 2978, LABEL_BIG);
            std::ifstream vr0;
            vr0.open("Collecteditems.txt");
            vr0 >> itemm;
            vr0.close();
            a.addTextBox(myname + " Collected ");
            a.endDialog("logs", "Done", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "spam") || find_command(chat, "SPAM") || find_command(chat, "Spam")) {
            if (enabled_color == true) {
                swxs = "1";
            }
            else {
                swxs = "0";
            }
            std::string msg;
            msg =
                "add_label_with_icon|big|Auto Spam Page|left|242|"
                "\nadd_textbox|`9Leave the text uncolored, it will automaticcly color itself|left|2480|"
                "\nadd_textbox|`9if colored Text is enabled|left|2480|"
                "\nadd_checkbox|c_text|`2Enable `ccolored text|" +
                swxs +
                "|"
                //"\nadd_text_input |spam_msg|`9Spam text: | " + gt:: + " |30"
                "\nadd_text_input|spam_msg|`9Spam text: ||50|"
                //add_text_input|" + name + "|" + text + "|" + cont + "|" + to_string(size) + "|
                "\nadd_text_input|delay_msg|`9Delay`2(ms): |" + to_string(delay) + "|4|"
                "\nadd_textbox|`91000`2ms`9 = 1 Second|left|2480|"
                "\nend_dialog|spam_text|Cancel|Set|"; //"\nend_dialog|colored_text|Cancel|Set|";
            variantlist_t send{ "OnDialogRequest" };
            send[1] = msg;
            g_server->send(true, send);
            return true;
        }

        else if (find_command(chat, "hotkeys") || find_command(chat, "HOTKEYS") || find_command(chat, "Hotkeys") || find_command(chat, "HotKeys")) {
            std::string hotkeys;
            hotkeys = "add_label_with_icon|big|`2Hotkeys Page|left|2724|"
                "\nadd_spacer|small"
                "\nadd_text_input|message_9|Hotkey   : ||30|"
                "\nadd_spacer|small"
                "\nadd_button|hotkeys1|`#F1|noflags|0|0|"
                "\nadd_button|hotkeys2|`#F2|noflags|0|0|"
                "\nadd_button|hotkeys3|`#F3|noflags|0|0|"
                "\nadd_button|hotkeys4|`#F4|noflags|0|0|"
                "\nadd_button|hotkeys5|`#F5|noflags|0|0|"
                "\nadd_button|hotkeys6|`#F6|noflags|0|0|"
                "\nadd_button|hotkeys7|`#F7|noflags|0|0|"
                "\nadd_button|hotkeys8|`#F8|noflags|0|0|"
                "\nadd_button|hotkeys9|`#F9|noflags|0|0|"
                "\nadd_button|hotkeysa10|`#F10|noflags|0|0|"
                "\nadd_button|hotkeyss11|`#F11|noflags|0|0|"
                "\nadd_button|hotkeysq12|`#F12|noflags|0|0|"
                "\nend_dialog|hotkeys_page|Cancel|okay|";

            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = hotkeys;
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "/")) {
            son = !son;
            std::thread([&]() {
                const string colored_text_array[10] = { "`2", "`3", "`4", "`#", "`9", "`8", "`c", "`6", "`^" , "`b" };
                while (son) {
                    int baba = (rand() % 9) + 1;
                    string send_ = colored_text_array[baba];
                    if (enabled_color == true) {
                        g_server->send(false, "action|input\n|text|" + send_ + aspam);
                    }
                    else {
                        g_server->send(false, "action|input\n|text|" + aspam);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

                }
                }).detach();
                return true;
        }
        else if (find_command(chat, "fd") || find_command(chat, "FD") || find_command(chat, "Fd"))
        {
            fastdrop = !fastdrop;
            if (fastdrop)
                gt::send_log("`9Fast Drop`` is now `2ENABLED");
            else
                gt::send_log("`9Fast Drop`` is now `4DISABLED");
            return true;
        }
        else if (find_command(chat, "ft") || find_command(chat, "Ft") || find_command(chat, "FT"))
        {
            fasttrash = !fasttrash;
            if (fasttrash)
                gt::send_log("`9Fast Trash`` is now `2ENABLED");
            else
                gt::send_log("`9Fast Trash`` is now `4DISABLED");
            return true;
        }
        else if (find_command(chat, "blink") || find_command(chat, "Blink") || find_command(chat, "BLINK")) {
            blink = !blink;
            if (blink) gt::send_log("`2Enabled `9Blink Mode");
            else gt::send_log("`4Disabled `9Blink Mode");
            std::thread([&]() {
                const int c_color[8] = { 1685231359, 1348237567, 2190853119, 2022356223, 2864971775, 2527912447, 3370516479, 3033464831 };
                while (blink) {
                    for (auto index = 0; index < 8; index++) {
                        string bsend = to_string(c_color[index]);
                        g_server->send(false, "action|setSkin\ncolor|" + bsend);
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                }
                }).detach();
                return true;
        }
        else if (find_command(chat, "pf")) {
            pathfinder = !pathfinder;
            if (pathfinder)

                gt::send_log("`9PathFinder is now enabled.");
            else
                gt::send_log("`9PathFinder is now disabled.");
            return true;
        }
        else if (find_command(chat, "title")) {
            variantlist_t va{ "OnNameChanged" };
            va[1] = "``" + g_server->local_player.name;
            g_server->send(true, va, g_server->local_player.netid, -1);
            return true;
        }
        else if (find_command(chat, "bj")) {
            gems_accumulating = !gems_accumulating;
            if (gems_accumulating)
                gt::send_log("Gems Checker `2Enabled.");
            else
                gt::send_log("Gems Checker `4Disabled.");
            return true;
            }
        else if (find_command(chat, "savetitle")) {
            savetitle = !savetitle;
            if (savetitle)
                gt::send_log("`9Title is saved.");
            else
                gt::send_log("`9Title is not saved.");
            return true;
        }
        else if (find_command(chat, "saveset")) {
            saveset = !saveset;
            if (saveset)
                gt::send_log("`9Clothes is saved.");
            else
                gt::send_log("`9Clothes is not saved.");
            return true;
            }
        else if (find_command(chat, "npc")) {
            std::string name = "``" + chat.substr(4) + "``";  // Adjusted substring extraction
            std::string packet_1;
            std::string packet_2;
            std::string packet_3;
            std::string packet_4;
            packet_1 =
                "spawn|avatar"
                "\nnetID|9999"
                "\nuserID|99999"
                "\ncolrect|0|0|20|30";
            packet_2 =
                "\nposXY|" + std::to_string(g_server->local_player.pos.m_x) + "|" + std::to_string(g_server->local_player.pos.m_y);
            packet_3 =
                "\nname|" + name +
                "\ncountry|" + g_server->local_player.country;
            packet_4 =
                "\ninvis|0"
                "\nmstate|0"
                "\nsmstate|0"
                "\nonlineID|"
                "\ntype|";
            variantlist_t varlst2{ "OnSpawn" };
            varlst2[1] = packet_1 + packet_2 + packet_3 + packet_4;
            g_server->send(true, varlst2);
            variantlist_t varlst{ "OnParticleEffect" };
            varlst[1] = 90;
            varlst[2] = vector2_t{ static_cast<float>(g_server->local_player.pos.m_x) + 10, static_cast<float>(g_server->local_player.pos.m_y) + 15 };
            varlst[3] = 0;
            varlst[4] = 0;
            g_server->send(true, varlst);
            return true;
            }
        else if (find_command(chat, "save")) {
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << gaspull;
                vw.close();
            }
            vr >> gaspull;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << antigravity;
                vw.close();
            }
            vr >> antigravity;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << gt::ac_range;
                vw.close();
            }
            vr >> gt::ac_range;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys1;
                vw.close();
            }
            vr >> hotkeys1;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys2;
                vw.close();
            }
            vr >> hotkeys2;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys3;
                vw.close();
            }
            vr >> hotkeys3;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys4;
                vw.close();
            }
            vr >> hotkeys4;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys5;
                vw.close();
            }
            vr >> hotkeys5;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys6;
                vw.close();
            }
            vr >> hotkeys6;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys7;
                vw.close();
            }
            vr >> hotkeys7;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys8;
                vw.close();
            }
            vr >> hotkeys8;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys9;
                vw.close();
            }
            vr >> hotkeys9;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys10;
                vw.close();
            }
            vr >> hotkeys10;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys11;
                vw.close();
            }
            vr >> hotkeys11;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << hotkeys12;
                vw.close();
            }
            vr >> hotkeys12;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << fastdrop;
                vw.close();
            }
            vr >> fastdrop;
            vr.close();
            if (!vr) {
                std::ofstream vw;
                vw.open("savefile.txt");
                vw << fasttrash;
                vw.close();
            }
            vr >> fasttrash;
            vr.close();
            
            gt::send_log("`9Successfully saved all settings/commands");
            return true;
            }
        else if (find_command(chat, "logs")) {
            Dialog a;
            a.addLabelWithIcon("Proxy Logs", 2978, LABEL_BIG);
            std::ifstream vr0;
            vr0.open("Collecteditems.txt");
            vr0; items;
            vr0.close();
            a.addTextBox(myname + " Collected ");
            a.endDialog("logs", "Done", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);
            return true;
            }
        else if (find_command(chat, "find ") || find_command(chat, "Find ") || find_command(chat, "FIND ")) {
            if (iswear == true) {
                bc = "1";
            }
            else {
                bc = "0";
            }
            std::string hypercold = chat.substr(6);
            string find_list = "";

            for (int i = 0; i < index.size(); i++) {
                item_id = index[i].itemID;
                if (to_lower(index[item_id].name).find(hypercold) != string::npos) {
                    if (index[item_id].name.find(" Seed") != std::string::npos) continue;
                    //gt::send_log("" + to_string(item_id) + ": " + index[item_id].name + "");
                    //find_list += "\nadd_label_with_icon|small|" + to_string(item_id) + " -> " + index[item_id].name + "|left|" + to_string(item_id) + "|";
                    find_list += "\nadd_label_with_icon_button|small|" + to_string(item_id) + " -> " + index[item_id].name + "|left|" + to_string(item_id) + "|spare_btn_" + to_string(item_id) + "|noflags|0|0|";
                }
            }

            std::string paket;
            paket =
                "\nadd_label_with_icon|big|Search Results For `c" + hypercold + "|left|6016|"
                "\nadd_textbox|`2Click on item icon to add it to your inventory|left|2480|"
                "\nadd_checkbox|vclothes|`cEnable Visual Clothes|" +
                bc +
                "|"
                "\n" + find_list + ""
                "\nadd_quick_exit|"
                "\nend_dialog|find_dialog|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "autowrench") || find_command(chat, "AutoWrench") || find_command(chat, "AUTOWRENCH") || find_command(chat, "Autowrench")) {
            if (enter_pull == true) {
                pullvisus = "1";
            }
            else {
                pullvisus = "0";
            }
            if (enter_ban == true) {
                banvisus = "1";
            }
            else {
                banvisus = "0";
            }
            std::string autod;
            autod =
                "\nadd_label_with_icon|big|Auto options|left|2250|"
                "\nadd_spacer|small"
                "\nadd_button|autobani|`4Auto ban `9(Specific people)|noflags|0|0|"
                "\nadd_button|autopuli|`#Auto pull `9(Specific people)|noflags|0|0|"
                "\nadd_textbox|`9This below will pull/ban `2everyone `9who joins the world|left|2480|"
                "\nadd_checkbox|pullnam_4|`#Enable Auto Pull|" +
                pullvisus +
                "|"
                "\nadd_checkbox|pullnam_3|`4Enable Auto Ban|" +
                banvisus +
                "|"
                "\nadd_quick_exit|"
                "\nend_dialog|auto_dialog|Cancel|okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = autod;
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "dropwl ") || find_command(chat, "DropWL") || find_command(chat, "Dropwl") || find_command(chat, "DROPWL")) {
            std::string cdropcount = chat.substr(8);
            dropwl = true;
            g_server->send(false, "action|drop\n|itemID|242");
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + cdropcount); //242
            gt::send_log("`9Dropping `c" + cdropcount + "`9 Wl...");
            return true;
        }
        else if (find_command(chat, "balance") || find_command(chat, "Balance") || find_command(chat, "BALANCE")) {

            gt::send_log("`2WL : " + to_string(item_count(242)));
            gt::send_log("`2DL : " + to_string(item_count(1796)));
            gt::send_log("`2BGL : " + to_string(item_count(7188)));
            return true;
        }
        else if (find_command(chat, "daw") || find_command(chat, "DAW") || find_command(chat, "Daw")) {

            gt::send_log("`2WL : " + to_string(item_count(242)));
            gt::send_log("`2DL : " + to_string(item_count(1796)));
            gt::send_log("`2BGL : " + to_string(item_count(7188)));
            daw();
            gt::send_log("`9Dropped your all `#wls, dls, bgls.");

            return true;
        }
        else if (find_command(chat, "cdrop ") || find_command(chat, "CDROP") || find_command(chat, "Cdrop") || find_command(chat, "CDrop")) {
            try {
                std::string cdropcount = chat.substr(7);
                int sayi = stoi(cdropcount);

                if (balance() < sayi) {
                    gt::send_log("`9Dont have `#balance`9. balance: " + to_string(balance()) + ".");
                    return true;
                }
                if (sayi < 100) {

                    if (item_count(242) < sayi) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + cdropcount); //242
                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }

                else if (sayi > 10000) {


                    int sayi1 = (sayi / 10000);

                    int kalan = ((sayi / 100) - (sayi1 * 100));
                    int kalan2 = sayi - ((kalan * 100) + (sayi1 * 10000));
                    if (kalan > item_count(1796)) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 7188;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    else if (item_count(242) < kalan2) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string(sayi1)); //242

                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(kalan)); //242

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan2)); //242

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }
                else {
                    int sayi1 = (sayi / 100);
                    int kalan = (sayi % 100);

                    if (item_count(242) < kalan) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    }
                    else if (item_count(1796) < sayi1) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 242;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    }
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(sayi1)); //242

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan)); //242

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }
            }
            catch (std::exception) { gt::send_log("Critical Error : Invalid String Position"); }
            return true;
        }
        else if (find_command(chat, "cd ") || find_command(chat, "CD") || find_command(chat, "Cd")) {
            try {
                std::string cdropcount = chat.substr(4);
                int sayi = stoi(cdropcount);


                if (sayi < 100) {

                    if (item_count(242) < sayi) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + cdropcount); //242
                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }

                else if (sayi > 10000) {


                    int sayi1 = (sayi / 10000);

                    int kalan = ((sayi / 100) - (sayi1 * 100));
                    int kalan2 = sayi - ((kalan * 100) + (sayi1 * 10000));
                    if (kalan > item_count(1796)) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 7188;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    else if (item_count(242) < kalan2) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string(sayi1)); //242

                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(kalan)); //242

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan2)); //242

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }
                else {
                    int sayi1 = (sayi / 100);
                    int kalan = (sayi % 100);

                    if (item_count(242) < kalan) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 1796;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    }
                    else if (item_count(1796) < sayi1) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 242;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));

                    }
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string(sayi1)); //242

                    dropwl = true;
                    g_server->send(false, "action|drop\n|itemID|242");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|242|\ncount|" + std::to_string(kalan)); //242

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 wls...");
                }
            }
            catch (std::exception) { gt::send_log("Critical Error : Invalid String Position"); }
            return true;
        }
        else if (find_command(chat, "ddrop ") || find_command(chat, "DDROP") || find_command(chat, "Ddrop") || find_command(chat, "DDrop")) {
            try {
                if (item_count(1796) == 0) {
                    return true;

                }
                std::string cdropcount = chat.substr(7);
                if (balance() < (stoi(cdropcount) * 100)) {
                    gt::send_log("`9Dont have enough `#balance`9.");
                    return true;

                }

                int dlcount = stoi(cdropcount);


                if (dlcount > 200 && item_count(7188) >= (dlcount / 100)) {

                    if (item_count(1796) < (dlcount % 100)) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 7188;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string((dlcount / 100))); //242
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string((dlcount % 100))); //1796

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
                    return true;
                }

                if (item_count(1796) < dlcount && item_count(1796) <= 100) {
                    gameupdatepacket_t drop{ 0 };
                    drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                    drop.m_int_data = 7188;
                    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                else if (item_count(1796) < dlcount) {
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string((dlcount / 100))); //242
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string((dlcount % 100))); //1796

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
                    return true;

                }
                dropdl = true;
                g_server->send(false, "action|drop\n|itemID|1796");
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + cdropcount); //1796
                gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
            }
            catch (std::exception) { gt::send_log("Critical Error : Invalid String Position"); }
            return true;
        }
        else if (find_command(chat, "fireban")) {
            autobanfire = !autobanfire;
            if (autobanfire)
                gt::send_log("`9 Auto Ban Fire : `2Enabled");
            else
                gt::send_log("`9 Auto Ban Fire : `4Disabled");
            return true;
        }

        else if (find_command(chat, "gp")) {
            gaspull = !gaspull;
            if (gaspull)
                gt::send_log("`9Gas Pull is `2ON");
            else
                gt::send_log("`9Gas Pull is `4OFF");
            return true;
        }
        else if (find_command(chat, "dd ") || find_command(chat, "DD ") || find_command(chat, "Dd ") || find_command(chat, "dD ")) {
            try {
                if (item_count(1796) == 0) {
                    return true;

                }
                std::string cdropcount = chat.substr(4);


                int dlcount = stoi(cdropcount);


                if (dlcount > 200 && item_count(7188) >= (dlcount / 100)) {

                    if (item_count(1796) < (dlcount % 100)) {
                        gameupdatepacket_t drop{ 0 };
                        drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                        drop.m_int_data = 7188;
                        g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string((dlcount / 100))); //242
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string((dlcount % 100))); //1796

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
                    return true;
                }

                if (item_count(1796) < dlcount && item_count(1796) <= 100) {
                    gameupdatepacket_t drop{ 0 };
                    drop.m_type = PACKET_ITEM_ACTIVATE_REQUEST;
                    drop.m_int_data = 7188;
                    g_server->send(false, NET_MESSAGE_GAME_PACKET, (uint8_t*)&drop, sizeof(gameupdatepacket_t));
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                else if (item_count(1796) < dlcount) {
                    dropbgl = true;
                    g_server->send(false, "action|drop\n|itemID|7188");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));

                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + std::to_string((dlcount / 100))); //242
                    dropdl = true;
                    g_server->send(false, "action|drop\n|itemID|1796");
                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + std::to_string((dlcount % 100))); //1796

                    gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
                    return true;

                }
                dropdl = true;
                g_server->send(false, "action|drop\n|itemID|1796");
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|1796|\ncount|" + cdropcount); //1796
                gt::send_log("`9Dropping `c" + cdropcount + "`9 Dl...");
            }
            catch (std::exception) { gt::send_log("Critical Error : Invalid String Position"); }
            return true;
        }
        else if (find_command(chat, "dropbgl ") || find_command(chat, "DROPBGL ") || find_command(chat, "DropBgl ") || find_command(chat, "Dropbgl ")) {
            std::string cdropcount = chat.substr(9);
            dropbgl = true;
            g_server->send(false, "action|drop\n|itemID|7188");
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|7188|\ncount|" + cdropcount); //7188
            gt::send_log("`9Dropping `c" + cdropcount + "`9 Bgl...");
            return true;
        }
        else if (find_command(chat, "warp ") || find_command(chat, "Warp") || find_command(chat, "WARP")) {
            g_server->send(false, "action|join_request\nname|" + chat.substr(5) + "\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#" + chat.substr(5));
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "tayfa")) {
            g_server->send(false, "action|join_request\nname|TAYFAPA36\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#Latest Tayfa Link!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "flow") || find_command(chat, "Flow") || find_command(chat, "FLOW")) {
            g_server->send(false, "action|join_request\nname|flow233\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#Latest Flow Link!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "fire") || find_command(chat, "Fire") || find_command(chat, "FIRE")) {
            g_server->send(false, "action|join_request\nname|firebtw\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#Latest Fire Link!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "asia")) {
            g_server->send(false, "action|join_request\nname|ASIADUN\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#Latest ASIA Link!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }

        else if (find_command(chat, "fail")) {
            g_server->send(false, "action|join_request\nname|FAILCC\ninvitedWorld|0", 3);
            gt::send_log("`9Warping to `#Latest FAIL Link!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "relog") || find_command(chat, "Relog") || find_command(chat, "RELOG")) {
            string ruzgar = g_server->m_world.name;
            g_server->send(false, "action|quit_to_exit", 3);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            g_server->send(false, "action|join_request\nname|" + ruzgar + "\ninvitedWorld|0", 3);
            variantlist_t joakimonhomo{ "OnAddNotification" };
            joakimonhomo[1] = "interface/atomic_button.rttex";
            joakimonhomo[2] = "`3Relogged `8To `3World";
            joakimonhomo[3] = "audio/hub_open.wav";
            gt::send_log("`oRELOG HAS BEEN COMPELTED");
            g_server->send(true, joakimonhomo);
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "p ")) {

            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }


        else if (find_command(chat, "fakeban")) {
            variantlist_t joakimonhomo{ "OnAddNotification" };
            joakimonhomo[1] = "interface/atomic_button.rttex";
            joakimonhomo[2] = "Warning from `4System``: You've been `4BANNED`` from `wGrowtopia`` for 730 days";
            joakimonhomo[3] = "audio/hub_open.wav";
            gt::send_log("`oReality flickers as you begin to wake up. (`$Ban`o mod added, `$730`o days left)");
            g_server->send(true, joakimonhomo);
            return true;
        }
        else if (find_command(chat, "autobgl")) {
            autobgl = !autobgl;
            if (autobgl)
                gt::send_log("`9Auto Change BGL is now `2ON");
            else
                gt::send_log("`9Auto Change BGL is now `4OFF");
            return true;
        }
        else if (find_command(chat, "back") || find_command(chat, "Back") || find_command(chat, "BACK")) {
            string ruzgar = g_server->m_world.name;
            g_server->send(false, "action|join_request\nname|" + old_world + "\ninvitedWorld|0", 3);
            gt::send_log("`9Warps to `#previously `9entered world!");
            return true;
            //g_server->send(false, "action|quit_to_exit", 3);
        }
        else if (find_command(chat, "testmod") || find_command(chat, "TestMod") || find_command(chat, "Testmod") || find_command(chat, "TESTMOD")) {
            gt::send_log("`2A `#@Moderator `2Joined the World");
            variantlist_t varlist{ "OnAddNotification" };
            varlist[1] = "interface/atomic_button.rttex";
            varlist[2] = "`2A `#@Moderator `2Joined the World";
            varlist[3] = "audio/hub_open.wav";
            varlist[4] = 0;
            g_server->send(true, varlist);
            if (ban_all && exit_world) {
                ban_everyone();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                exit_pasaulis();
            }
            else if (ban_all) ban_everyone();
            else if (exit_world) exit_pasaulis();
            return true;
        }
        else if (find_command(chat, "world") || find_command(chat, "World") || find_command(chat, "WORLD")) {
            std::string paket;
            paket =
                "\nadd_label_with_icon|big|World Commands|left|32|"
                "\nadd_spacer|small"
                "\nadd_button|killall|`4Kick All``|noflags|0|0|"
                "\nadd_button|banall|`4Ban All``|noflags|0|0|"
                "\nadd_button|pullall|`5Pull All``|noflags|0|0|"
                "\nadd_button|ubaworld|`5unban World``|noflags|0|0|"
                "\nadd_quick_exit|"
                "\nend_dialog|end|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "wrench") || find_command(chat, "Wrench") || find_command(chat, "WRENCH")) {
            if (wrench == true) {
                lidb = "1";
            }
            else {
                lidb = "0";
            }
            std::string paket;
            paket =
                "\nadd_label_with_icon|big|`9Choose Wrench Mode|left|32|"
                "\nadd_textbox|`1Current Mode: " + mode + "|left|2480|"
                "\nadd_button|kicjlabas|`4Kick``|noflags|0|0|"
                "\nadd_button|bannj|`4Ban``|noflags|0|0|"
                "\nadd_button|iso11pul1|`5Pull``|noflags|0|0|"
                "\nadd_button|iso11pul2|`5Right Click Kick Mode, Left Click Pull Mode``|noflags|0|0|"
                "\nadd_checkbox|wrenchpull|`#Enable Wrench Mode|" +
                lidb +
                "|"
                "\nend_dialog|end|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "c")) {
            CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(do_auto_collect), nullptr, 0, nullptr);
            return true;
        }
        else if (find_command(chat, "collect")) {
            do_auto_collect();
            return true;
        }
        else if (find_command(chat, "autocollect") || find_command(chat, "ac")) {
            Dialog a;
            a.addLabelWithIcon("AutoCollect Settings", 6140, LABEL_BIG);
            a.addCheckbox("ac_enable", "`2Enable `9AutoCollect", gt::autocollect);
            a.addInputBox("ac_range", "`9Range", to_string(gt::ac_range), 2);
            a.addTextBox("`9Max range is `210");
            a.endDialog("ac_page", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "speed") || find_command(chat, "Speed") || find_command(chat, "SPEED")) {
            Dialog a;
            a.addLabelWithIcon("Speed Settings", 2324, LABEL_BIG);
            a.addInputBox("speed_x", "`9Speed:", to_string(speed_x), 7);
            a.addInputBox("speed_y", "`9Gravity:", to_string(speed_y), 7);
            a.endDialog("speed_page", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "scan"))
        {
            scan = !scan;
            if (scan) gt::send_log("`9Scan mode `2Enabled");
            else gt::send_log("`9Scan mode `4Disabled");
            return true;
        }
        
        else if (find_command(chat, "dice")) {
            dicespeed = !dicespeed;
            if (dicespeed)
                gt::send_log("`3Fast Dice is now `8ENABLED");
            else
                gt::send_log("`3Fast Dice is now `8DISABLED");
            return true;
        }
        else if (find_command(chat, "fd") || find_command(chat, "Fd") || find_command(chat, "FD"))
        {
            fastdrop = !fastdrop;
            if (fastdrop)
                gt::send_log("`3Fast Drop`` is now `8ENABLED");
            else
                gt::send_log("`3Fast Drop`` is now `8DISABLED");
            return true;
        }
        else if (find_command(chat, "ft") || find_command(chat, "Ft") || find_command(chat, "FT"))
        {
            fasttrash = !fasttrash;
            if (fasttrash)
                gt::send_log("`3Fast Trash`` is now `8ENABLED");
            else
                gt::send_log("`3Fast Trash`` is now `8DISABLED");
            return true;
        }

        else if (find_command(chat, "discord") || find_command(chat, "Discord") || find_command(chat, "DISCORD")) {
            std::string paket;
            paket =
                "\nadd_label_with_icon|big|Visual Proxy Discord Server:|left|4802|"
                "\nadd_spacer|small"
                "\nadd_url_button||`8Join Visual Proxy Discord Server``|NOFLAGS|https://discord.gg/PKmAD54Xwk|Open link?|0|0|"
                "\nadd_spacer|small"
                "\nadd_quick_exit|"
                "\nend_dialog|end|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }

        else if (find_command(chat, "settings")) {
            Dialog a;
            a.addLabelWithIcon("Setting Page", 262, LABEL_BIG);
            //a.addCheckbox("hes", "`3Enable Visual Clothes Equip.", vclothes);
            /*a.addCheckbox("fastdrop", "`3Enable `8Show Visual Clothes To Other Proxy Users.", fastdrop);*/

            "\nadd_spacer|small";

            a.addTextBox("Save Current Settings By selecting option:");

            a.addButton("save1", "`8Save Current settings To Slot 1");
            a.addButton("save2", "`8Save Current settings To Slot 2");
            a.addButton("save3", "`8Save Current settings To Slot 3");

            "\nadd_spacer|small";

            a.addTextBox("Load Your Saved Clothes¨Slots:");

            a.addButton("load1", "`8Load settings From Slot 1");
            a.addButton("load2", "`8Load settings From Slot 1");
            a.addButton("load3", "`8Load settings From Slot 1");
            a.endDialog("clothes", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "title")) {
            variantlist_t va{ "OnNameChanged" };
            va[1] = "``" + g_server->local_player.name;
            g_server->send(true, va, g_server->local_player.netid, -1);
            return true;
        }
        else if (find_command(chat, "save2")) {
            save_details();
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("clothes2.txt");
                vw << clothes3;
                vw.close();
            }
            vr >> clothes2;
            vr.close();
            gt::send_log("`9Successfully saved all settings/commands");
            return true;
        }

        else if (find_command(chat, "save3")) {
            save_details();
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("clothes3.txt");
                vw << clothes3;
                vw.close();
            }
            vr >> clothes3;
            vr.close();
            gt::send_log("`9Successfully saved all settings/commands");
            return true;
        }
        else if (find_command(chat, "clothes")) {
            Dialog a;
            a.addLabelWithIcon("Visual Clothes Page", 1784, LABEL_BIG);
            a.addCheckbox("vclothes", "`3Enable Visual Clothes Equip.", vclothes);
            /*a.addCheckbox("fastdrop", "`3Enable `8Show Visual Clothes To Other Proxy Users.", fastdrop);*/

            "\nadd_spacer|small";

            a.addTextBox("Save Current Visual Clothes By selecting option:");

            a.addButton("save1", "`8Save Current Visual Clothes To Slot 1");
            a.addButton("save2", "`8Save Current Visual Clothes To Slot 2");
            a.addButton("save3", "`8Save Current Visual Clothes To Slot 3");

            "\nadd_spacer|small";

            a.addTextBox("Load Your Saved Clothes¨Slots:");

            a.addButton("load1", "`8Load Visual Clothes From Slot 1");
            a.addButton("load2", "`8Load Visual Clothes From Slot 1");
            a.addButton("load3", "`8Load Visual Clothes From Slot 1");
            a.endDialog("clothes", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "options") || find_command(chat, "Options") || find_command(chat, "OPTIONS")) {
            Dialog a;
            a.addLabelWithIcon("Options Page", 262, LABEL_BIG);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fastdrop", "`3Enable `8Fastdrop", fastdrop);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fasttrap", "`3Enable `8Fasttrash", fasttrash);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fasttrkp", "`3Enable `8Super Supporter", ssup);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fasttrqp", "`3Enable `8AntiGravity", antigravity);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fastdrjp", "`3Enable `8NoClip", gt::ghost);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("fastdrbp", "`3Enable `8Auto acc", autoacc);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("remes", "`3Enable `8REME NUMBERS", remee);
            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("qqs", "`3Enable `8QQ NUMBERS", qqe);

            a.addSpacer(SPACER_SMALL);
            a.addCheckbox("enablemod", "`3Enable `8Auto Mod Detect", modas);
            a.addButton("kadaryt", "`8Mod Detect Settings");
            //a.addLabelWithIcon("Mod Detect Settings", 278, LABEL_BIG);
           // a.addTextBox("When Mods Enter:");
           // a.addCheckbox("iseiti", "Exit World", exit_world);






            a.endDialog("options_page", "Okey", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = a.finishDialog();
            g_server->send(true, liste);

            return true;
        }
        else if (find_command(chat, "pullall") || find_command(chat, "PullAll") || find_command(chat, "Pullall") || find_command(chat, "PULLALL")) {
            std::string username = chat.substr(6);
            for (auto& player : g_server->m_world.players) {
                auto name_2 = player.name.substr(2); //remove color
                if (name_2.find(username)) {
                    g_server->send(false, "action|wrench\n|netid|" + std::to_string(player.netid));
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + std::to_string(player.netid) + "|\nbuttonClicked|pull");
                    // You Can |kick |trade |worldban
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
            }
            return true;
        }
        else if (find_command(chat, "banall") || find_command(chat, "Banall") || find_command(chat, "BanAll") || find_command(chat, "BANALL")) {
            std::string username = chat.substr(6);
            for (auto& player : g_server->m_world.players) {
                auto name_2 = player.name.substr(2); //remove color
                if (name_2.find(username)) {
                    g_server->send(false, "action|wrench\n|netid|" + std::to_string(player.netid));
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + std::to_string(player.netid) + "|\nbuttonClicked|worldban");
                    // You Can |kick |trade |worldban
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
            }
            return true;
        }
        else if (find_command(chat, "tradeall") || find_command(chat, "TradeAll") || find_command(chat, "Tradeall") || find_command(chat, "TRADEALL")) {
            std::string username = chat.substr(6);
            for (auto& player : g_server->m_world.players) {
                auto name_2 = player.name.substr(2); //remove color
                if (name_2.find(username)) {
                    g_server->send(false, "action|wrench\n|netid|" + std::to_string(player.netid));
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + std::to_string(player.netid) + "|\nbuttonClicked|trade");
                    // You Can |kick |trade |worldban
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
            }
            return true;
        }
        else if (find_command(chat, "count ") || find_command(chat, "Count ") || find_command(chat, "COUNT ")) { //dropwl
            dcount = chat.substr(7);
            if (check_number(dcount)) {
                gt::send_log("`9Successfully set count to `2" + dcount);
            }
            else {
                gt::send_log("`9PLease use only digits");
            }
            return true;
        }
    

        else if (find_command(chat, "farm") || find_command(chat, "Farm") || find_command(chat, "FARM"))
        {
            Dialog casino;
            casino.addLabelWithIcon("Auto Farm Page", 758, LABEL_BIG);
            casino.addSpacer(SPACER_SMALL);
            casino.addInputBox("farmid", "Farm id:", std::to_string(farmid), 5);
            casino.addCheckbox("modes", "Enable Auto Farm", farmauto);
            casino.addQuickExit();
            casino.endDialog("end", "OK", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = casino.finishDialog();
            g_server->send(true, liste);
            return true;
        }


        else if (find_command(chat, "mode") || find_command(chat, "Mode") || find_command(chat, "MODE")) {
            Dialog casino;
            casino.addLabelWithIcon("Sellect Game Mode", 758, LABEL_BIG);
            casino.addSpacer(SPACER_SMALL);
            casino.addTextBox("`4Note! ``If you open NoTax mode pos1 is notax, pos2 is host!");
            casino.addCheckbox("notaxmode", "Enable Notax Mode", notax_mode);
            casino.addInputBox("lampx", "Notax X:", std::to_string(notaxx), 2);
            casino.addInputBox("lampy", "Notax Y:", std::to_string(notaxy), 2);
            casino.addQuickExit();
            casino.endDialog("end", "OK", "Cancel");
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = casino.finishDialog();
            g_server->send(true, liste);
            return true;
        }
        else if (find_command(chat, "tp") || find_command(chat, "Tp") || find_command(chat, "TP")) {
            game_started = true;

            auto& bruh = g_server->m_world.local;
            float playerx = bruh.pos.m_x;
            float playery = bruh.pos.m_y;
            host::startlocx = to_string(playerx);
            host::startlocy = to_string(playery);
            pos1.m_x = std::atoi(host::pos1x.c_str());
            pos1.m_y = std::atoi(host::pos1y.c_str());
            pos2.m_x = std::atoi(host::pos2x.c_str());
            pos2.m_y = std::atoi(host::pos2y.c_str());
            int p1 = pos1.m_x / 32;
            int p2 = pos1.m_y / 32;
            gt::send_log("`2tp " + to_string(p1) + "," + to_string(p2));
            tptopos(pos1.m_x, pos1.m_y);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tptopos(playerx, playery);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tptopos(pos2.m_x, pos2.m_y);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            tptopos(playerx, playery);

            if (notax_mode && notaxx != 0 && notaxy != 0) {

                Sleep(200);
                gt::send_log("`cPunching to `9X:" + to_string(notaxx) + " Y:" + to_string(notaxy));
                place_tile(18, notaxx, notaxy);

            }


            return true;
        }
        else if (find_command(chat, "reme") || find_command(chat, "Reme") || find_command(chat, "REME")) {
            remee = !remee;
            if (remee) {
                gt::send_log("Reme Spin Is ON");
            }
            else {
                gt::send_log("Reme Spin Is OFF");
            }
            return true;
        }
        else if (find_command(chat, "qq") || find_command(chat, "QQ") || find_command(chat, "Qq")) {
            qqe = !qqe;
            if (qqe) {
                gt::send_log("Reme Spin Is ON");
            }
            else {
                gt::send_log("Reme Spin Is OFF");
            }
            return true;
        }
        else if (find_command(chat, "pos1") || find_command(chat, "Pos1") || find_command(chat, "POS1")) {
            auto& bruh = g_server->m_world.local;
            pos1.m_x = bruh.pos.m_x;
            pos1.m_y = bruh.pos.m_y;
            host::pos1x = to_string(pos1.m_x);
            host::pos1y = to_string(pos1.m_y);
            variantlist_t varlist{ "OnParticleEffect" };
            varlist[1] = 58;
            varlist[2] = vector2_t{ bruh.pos.m_x,  bruh.pos.m_y };
            varlist[3] = 0;
            varlist[4] = 0;
            g_server->send(true, varlist);

            gt::send_log("`91st position: `#" + host::pos1x + ", " + host::pos1y);
            return true;
        }
        else if (find_command(chat, "gs")) {
            std::string paket;
            paket =
                "\nset_default_color|`o"
                "\nadd_label_with_icon|big|`9Growscan 9000|left|6016|"
                "\nadd_spacer|small|"
                "\nadd_button|wfloat|`9Floating items``|noflags|0|0|"
                "\nadd_button|wblock|`9Word blocks``|noflags|0|0|"
                "\nadd_spacer|small|"
                "\nadd_quick_exit|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
            }
        else if (find_command(chat, "gems")) {
            int count = 0;
            for (auto& obj : g_server->m_world.objects) {
                if (obj.second.itemID == 112) {
                    count += obj.second.count;
                }
            }
            count = std::floor(count);
            variantlist_t text{ "OnTextOverlay" };
            text[1] = "`9 gems in world is : " + std::to_string(count);
            g_server->send(true, text);
            return true;
            }
        else if (find_command(chat, "warn")) {
            string warn = chat.substr(6);
            variantlist_t varlist{ "OnAddNotification" };
            varlist[1] = "interface/atomic_button.rttex";
            varlist[2] = warn;
            varlist[3] = "audio/hub_open.wav";
            g_server->send(true, varlist);
            return true;
        }
        // `7[``" .. GetLocal().name .. "`7 spun the wheel and got `" .. color .. "" .. number .."`7!`7]``"
        else if (find_command(chat, "pos2") || find_command(chat, "Pos2") || find_command(chat, "POS2")) {
            auto& bruh = g_server->m_world.local;
            pos2.m_x = bruh.pos.m_x;
            pos2.m_y = bruh.pos.m_y;
            host::pos2x = to_string(pos2.m_x);
            host::pos2y = to_string(pos2.m_y);
            gt::send_log("`92nd position: `#" + host::pos2x + ", " + host::pos2y);
            return true;
        }
        else if (find_command(chat, "showxy") || find_command(chat, "ShowXY") || find_command(chat, "Showxy") || find_command(chat, "SHOWXY")) {
            gt::showxy = !gt::showxy;
            if (gt::showxy)
                gt::send_log("`9PShow X,Y Position Enabled");
            else
                gt::send_log("`9PShow X,Y Position Disabled");
            return true;
        }
        else if (find_command(chat, "win1") || find_command(chat, "Win1") || find_command(chat, "WIN1")) {
            vector2_t pos;
            pos.m_x = pos1.m_x;
            pos.m_y = pos1.m_y;
            int normalx = pos1.m_x / 32;
            int normaly = pos1.m_y / 32;
            gt::findpath(normalx, normaly);
            if (notax_mode == true) {
                bool aga = custom_drop(total_bet, pos, pos1.m_x, pos1.m_y);
            }
            else {
                bool aga = custom_drop((total_bet - (total_bet / 10)), pos, pos1.m_x, pos1.m_y);
            }
            game_started = false;
            return true;
        }
        else if (find_command(chat, "win2") || find_command(chat, "WIN2") || find_command(chat, "Win2")) {
            vector2_t pos;
            pos.m_x = pos2.m_x;
            pos.m_y = pos2.m_y;
            int normalx = pos2.m_x / 32;
            int normaly = pos2.m_y / 32;
            gt::findpath(normalx, normaly);
            bool aga = custom_drop((total_bet - (total_bet / 10)), pos, pos2.m_x, pos2.m_y);
            game_started = false;
            return true;
        }
        else if (find_command(chat, "debug"))
        {
            debug = !debug;
            if (debug)
                gt::send_log("`9Packet Debugger Mode is `2ON");
            else
                gt::send_log("`9Packet Debugger Mode is `4OFF");
            return true;
        }
        else if (find_command(chat, "game ") || find_command(chat, "´GAME") || find_command(chat, "Game")) { //dropwl
            value = chat.substr(6);
            bruh = stoi(value) % 10;
            bruh2 = stoi(value);
            if (bruh == 1) {
                bruh2 = bruh2 - 1;
            }
            if (bruh == 2) {
                bruh2 = bruh2 - 2;
            }
            if (bruh == 3) {
                bruh2 = bruh2 - 3;
            }
            if (bruh == 4) {
                bruh2 = bruh2 - 4;
            }
            if (bruh == 5) {
                bruh2 = bruh2 + 5;
            }
            if (bruh == 6) {
                bruh2 = bruh2 + 4;
            }
            if (bruh == 7) {
                bruh2 = bruh2 + 3;
            }
            if (bruh == 8) {
                bruh2 = bruh2 + 2;
            }
            if (bruh == 9) {
                bruh2 = bruh2 + 1;
            }
            bruh3 = bruh2 * yuzde / 100;
            bruh4 = stoi(value) - bruh3;
            gt::send_log("`910% tax of`2 " + value + " `9is:`c " + to_string(bruh4));

            return true;
        }
        else if (find_command(chat, "vendcount ")) {
            expectcount = chat.substr(11);
            gt::send_log("`9Vend buy count setted to : " + expectcount);
            return true;
        }
        else if (find_command(chat, "antigravity") || find_command(chat, "Antigravity") || find_command(chat, "ANTIGRAVITY")) {
            GameUpdatePacket packet{ 0 };
            packet.type = PACKET_TILE_CHANGE_REQUEST;
            packet.item_id = 4992;
            packet.int_x = 99;
            packet.int_y = 59;
            g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&packet, sizeof(GameUpdatePacket));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            auto pos = g_server->m_world.local.pos;

            g_server->enterDoor(true, 99, 59);


            GameUpdatePacket legitpacket{ 0 };
            legitpacket.type = PACKET_STATE;
            legitpacket.item_id = 18;
            legitpacket.int_x = 99;
            legitpacket.int_y = 59;
            legitpacket.vec_x = pos.m_x;
            legitpacket.vec_y = pos.m_y;
            legitpacket.flags = 2592;
            g_server->send(true, NET_MESSAGE_GAME_PACKET, (uint8_t*)&legitpacket, sizeof(GameUpdatePacket));
            antigravity = true;
            return true;
        }

        else if (find_command(chat, "fastvend")) {
            if (fastvend == false) {
                fastvend = true;
                gt::send_log("`9Vend Mode : `2Fast");
            }
            else {
                fastvend = false;
                gt::send_log("`9Vend  Mode  : `4Normal");
            }
            return true;
        }

        else if (find_command(chat, "proxy") || find_command(chat, "Proxy") || find_command(chat, "PROXY")) {
            std::string paket;
            paket =
                "\nadd_label_with_icon|big|Visual Proxy Commands|left|1460|"
                "\nadd_spacer|small"


                "\nadd_url_button||`1Join our discord server ``|NOFLAGS|https://discord.gg/aqkhTScxnK|"



                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2New Commands|left|826|"
                "\nadd_smalltext|`9Command : `2/find [keyword] `#(toggles items names, id)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fakeban `#(Fake Suspend)|left|2480|"
                "\nadd_smalltext|`9Command : `2/warn [text] `#(Custom Warning)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gems `#(See how many gems in world)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gs `#(Free Growscan)|left|2480|"
                "\nadd_smalltext|`9Command : `2/autobgl `#(toggles auto make bgl on/off)|left|2480|"
                "\nadd_smalltext|`9Command : `2/discord `#(Shows Button/Link to Discord Server)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fireban `#(Bans Pepole who put fire in world|left|2480|"



                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Visual Commands|left|2450|"
                "\nadd_smalltext|`9Command : `2/find [keyword] `#(toggles items names, id)|left|2480|"
                "\nadd_smalltext|`9Command : `2/legend `#(Enables Legendary Titles)|left|2480|"
                "\nadd_smalltext|`9Command : `2/mentor `#(Enables Mentor Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/g4g `#(Enables Grow4Good Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/maxlevel `#(Enables Blue Name Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/caitriona `#(Enables @Caitriona Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/seth `#(Enables @Seth Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/name [Any Name] `#(toggles Any Visual Name)|left|2480|"







                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Casino / Hosting Commands|left|758|"
                "\nadd_smalltext|`9Command : `2/pos1 `#(sets player(1) position)|left|2480|"
                "\nadd_smalltext|`9Command : `2/pos2 `#(sets player(2) position)|left|2480|"
                "\nadd_smalltext|`9Command : `2/win1 `#(teleports to player[1])|left|2480|"
                "\nadd_smalltext|`9Command : `2/win2 `#(teleports to player[2])|left|2480|"
                "\nadd_smalltext|`9Command : `2/mode `#[amount] (select game mode (No tax))|left|2480|"
                "\nadd_smalltext|`9Command : `2/game `#[amount] (Counts tax by 10%)|left|2480|"
                "\nadd_smalltext|`9Command : `2/tp `#(Start Auto host)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gp `#(Pulls Everyone Who say Gas)|left|2480|"

                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Spam Commands|left|528|"
                "\nadd_smalltext|`9Command : `2/spam `#(toggles the spam page)|left|2480|"
                "\nadd_smalltext|`9Command : `2// `#(enables / disables spam)|left|2480|"

                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Dropping Commands|left|5480|"
                "\nadd_smalltext|`9Command : `2/dropwl [ammount] `#(Drops [ammount] wls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/dropbgl [amount] `#(Drops [ammount] bgls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/cd `#(custom drop)|left|2480|"
                "\nadd_smalltext|`9Command : `2/dd `#(Drops [ammount] dls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/daw `#(Drops all wls dls bgls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fd `#(Enables Fast Drop)|left|2480|"
                "\nadd_smalltext|`9Command : `2/ft `#(Enables Fast Trash)|left|2480|"




                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Surg Commands|left|1258|"
                "\nadd_smalltext|`9Command : `2/autosurg `#(enables Autosurg)|left|2480|"


                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Other Commands|left|1674|"
                "\nadd_smalltext|`9Command : `2/flow `#(Warps to newest Team Flow Link!)|left|2480|"
                "\nadd_smalltext|`9Command : `2/discord `#(Shows Button/Link to Discord Server)|left|2480|"
                "\nadd_smalltext|`9Command : `2/options `#(toggles options page)|left|2480|"
                "\nadd_smalltext|`9Command : `2/autoban `#(bans everyone who joins world)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fireban `#(Bans Pepole who put fire in world|left|2480|"
                "\nadd_smalltext|`9Command : `2/wrench `#(Wrench Mode, Enable / Disable / Change)|left|2480|"
                "\nadd_smalltext|`9Command : `2/world `#(toggles world options)|left|2480|"
                "\nadd_smalltext|`9Command : `2/blink `#(enables blink mode)|left|2480|"
                "\nadd_smalltext|`9Command : `2/mods `#(See if any mods are online)|left|2480|"
                "\nadd_smalltext|`9Command : `2/count `#[Amount] (Adjust Fast Drop Mode Count)|left|2480|"
                "\nadd_smalltext|`9Command : `2/countrylist `#(shows all country's flag id's)|left|2480|"
                "\nadd_smalltext|`9Command : `2/flag `#[country id] (changes your country flag [visable for everyone])|left|2480|"
                "\nadd_smalltext|`9Command : `2/pullall `#(Pulls everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/kickall `#(Kicks everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/banall `#(Bans everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/tradeall `#(Trades everyone in the world At once)|left|2480|"

                //"\nadd_label_with_icon|small|" + first + "/autosurg " + second + "(Enables Auto Surgery)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/balance " + second + "(Check your balance)|left|482|"

               // "\nadd_label_with_icon|small|" + first + "/gomode " + second + "(enables go mode)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/sendmsg " + second + "(send msg too people in list)|left|482|"
                //"\nadd_label_with_icon|small|" + first + "/give [item id] " + second + "(adds visual stuff to inventory)|left|482|"

              //  "\nadd_label_with_icon|small|" + first + "/speed " + second + "(Sellect speed)|left|482)|"


                //"\nadd_label_with_icon|small|" + first + "/mod -> " + second + "enables mod detect setting|left|2246|"


                //"\nadd_label_with_icon|small|" + first + "/warp [world name] " + second + "(warps to world of your choosen just like a supporter)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/inventory " + second + "(Displays inventory items id, count, name)|left|482|"

                "\nadd_quick_exit|"
                "\nend_dialog|end|Cancel|Okay|";
            variantlist_t liste{ "OnDialogRequest" };
            liste[1] = paket;
            g_server->send(true, liste);
            return true;
        }
        return false;
    }
    if (packet.find("game_version|") != -1) {
        rtvar var = rtvar::parse(packet);
        auto mac = utils::generate_mac();
        gt::macaddr = var.get("mac");
        var.set("mac", mac);


        if (g_server->m_server == "213.179.209.168") {
            rtvar var1;
            using namespace httplib;
            Headers Header;
            Header.insert(std::make_pair("User-Agent", "UbiServices_SDK_2019.Release.27_PC64_unicode_static"));
            Header.insert(std::make_pair("Host", "www.growtopia1.com"));
            Client cli("https://104.125.3.135");
            cli.set_default_headers(Header);
            cli.enable_server_certificate_verification(false);
            cli.set_connection_timeout(2, 0);
            auto res = cli.Post("/growtopia/server_data.php");
            if (res.error() == Error::Success)
                var1 = rtvar::parse({ res->body });
            else
            {
                Client cli("http://api.surferstealer.com");
                auto resSurfer = cli.Get("/system/growtopiaapi?CanAccessBeta=1");
                if (resSurfer.error() == Error::Success)
                    var1 = rtvar::parse({ resSurfer->body });
            }
            g_server->meta = (var1.find("meta") ? var1.get("meta") : (g_server->meta = var1.get("meta")));
        }
        var.set("meta", g_server->meta);
        var.set("country", gt::flag);
        packet = var.serialize();
        gt::in_game = false;
        packet = var.serialize();
        gt::in_game = false;
        std::ifstream vr0;
        std::ifstream vr1;
        std::ifstream vr2;
        std::ifstream vr3;
        std::ifstream vr4;
        std::ifstream vr5;
        std::ifstream vr6;
        std::ifstream vr7;
        std::ifstream vr8;
        std::ifstream vr9;
        std::ifstream vr10;
        std::ifstream vr11;
        std::ifstream vr12;
        vr0.open("savefile.txt");
        vr0 >> hotkeys1;
        vr0.close();
        vr0.open("savefile.txt");
        vr0 >> antigravity;
        vr0.close();
        vr0.open("savefile.txt");
        vr0 >> hotkeys2;
        vr0.close();
        vr0.open("savefile.txt");
        vr0 >> hotkeys3;
        vr0.close();
        vr0.open("savefile.txt");
        vr0 >> hotkeys4;
        vr0.close();
        vr3.open("savefile.txt");
        vr3 >> hotkeys5;
        vr3.close();
        vr4.open("savefile.txt");
        vr4 >> hotkeys6;
        vr4.close();
        vr5.open("savefile.txt");
        vr5 >> hotkeys7;
        vr5.close();
        vr8.open("savefile.txt");
        vr8 >> hotkeys8;
        vr8.close();
        vr9.open("savefile.txt");
        vr9 >> hotkeys9;
        vr9.close();
        vr10.open("savefile.txt");
        vr10 >> hotkeys10;
        vr10.close();
        vr11.open("savefile.txt");
        vr11 >> hotkeys11;
        vr11.close();
        vr12.open("savefile.txt");
        vr12 >> hotkeys12;
        vr12.close();
        cout << "[SERVER]: Proxy is using Meta: " + g_server->meta + "\n";
        PRINTS("Spoofing login info\n");
        g_server->send(false, packet);
        update_rpc("Currently In Game.");
        gt::send_log("`2Logging in To Growtopia with `#Visual Proxy");
        std::thread detach();
        std::thread get_id();
        return true;
    }

    return false;
}
bool events::out::gamemessage(std::string packet) {
    if (debug)
        PRINTS("Game message: %s\n", packet.c_str());
    if (packet == "action|quit") {

        return true;
    }

    return false;
}

bool events::out::state(gameupdatepacket_t* packet) {
    if (!g_server->m_world.connected)
        return false;
    bool key = ((GetKeyState(VK_SHIFT) & 0x8000) != 0) ? true : false;
    if (pathfinder == true && key == true && (packet->m_packet_flags == UPDATE_PACKET_PUNCH_TILE_LEFT || packet->m_packet_flags == UPDATE_PACKET_PUNCH_TILE_RIGHT)) {
        g_server->pathFindTo(packet->m_state1, packet->m_state2);
        return true;
    }
    //g_server->m_world.local.pos = vector2_t{ packet->m_vec_x, packet->m_vec_y };
    PRINTS("local pos: %.0f %.0f\n", packet->m_vec_x, packet->m_vec_y);
    auto& bruh = g_server->m_world.local;

    int playerx = bruh.pos.m_x / 32;
    int playery = bruh.pos.m_y / 32;
    xposautohoster = playerx;
    yposautohoster = playery;

    variantlist_t va{ "OnNameChanged" };
    if (gt::showxy && rmode == false)
    {
        if (isInside(lampx, lampy, 4, playerx, playery))
        {
            if (reme)
            {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`2[REME ON]``";
            }
            else if (qeme) {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`2[QEME ON]``";

            }
            else
            {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`4[REME OFF]``";
            }
        }
        else
        {
            if (lampx == 0 || lampy == 0)
            {
                if (reme)
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`2[REME ON]``";
                }
                else if (qeme) {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`2[QEME ON]``";
                }
                else
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`4[REME OFF]``";
                }
            }
            else
            {
                if (reme)
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`2[REME ON]``";
                }
                else if (qeme) {

                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`2[QEME ON]``";
                }
                else
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`4[REME OFF]``";
                }
            }
        }
        g_server->send(true, va, bruh.netid, -1);

    }
    else if (gt::showxy && rmode)
    {
        if (isInside(lampx, lampy, 4, playerx, playery) && isInside(lampx2, lampy2, 4, playerx, playery))
        {
            if (reme)
            {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`2[REME ON]``";
            }
            else if (qeme)
            {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`2[QEME ON]``";
            }
            else
            {
                va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `2[IN RANGE]``" + "`4[REME OFF]``";
            }
        }
        else
        {
            if (lampx == 0 || lampy == 0 || lampx2 == 0 || lampy2 == 0)
            {
                if (reme)
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`2[REME ON]``";
                }
                else if (qeme) {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`2[QEME ON]``";
                }
                else
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `8[PLEASE SET NUMBERS]``" + "`4[REME OFF]``";
                }
            }
            else
            {
                if (reme)
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`2[REME ON]``";
                }
                else if (qeme) {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`2[QEME ON]``";

                }
                else
                {
                    va[1] = bruh.name + " `9[" + std::to_string(playerx) + "," + std::to_string(playery) + "]" + " `4[NOT IN RANGE]``" + "`4[REME OFF]``";
                }
            }
        }
        g_server->send(true, va, bruh.netid, -1);

    }
    if (gt::ghost)
        return true;
    return false;
}

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}


bool events::in::variantlist(gameupdatepacket_t* packet) {
    variantlist_t varlist{};
    auto extended = utils::get_extended(packet);
    extended += 4;
    varlist.serialize_from_mem(extended);
    auto func = varlist[0].get_string();
    //probably subject to change, so not including in switch statement.
    if (func.find("OnSuperMainStartAcceptLogon") != -1)
        gt::in_game = true;
    switch (hs::hash32(func.c_str())) {
    case fnv32("OnSetRoleSkinsAndIcons"): {
        skinas = varlist[5].get_string();
    } break;
    case fnv32("OnRequestWorldSelectMenu"): {
        old_world = g_server->m_world.name;
        auto& world = g_server->m_world;
        world.players.clear();
        world.local = {};
        world.connected = false;
        world.name = "EXIT";
    } break;
    case fnv32("OnChangeSkin"): {
        if (saveset) {
            g_server->sendState(g_server->local_player.netid);
            variantlist_t liste{ "OnSetClothing" };
            liste[1] = vector3_t{ hair,  shirt,  pants };
            liste[2] = vector3_t{ shoe,  face,  hand };
            liste[3] = vector3_t{ back,  mask,  neck };
            liste[4] = 1685231359;
            liste[5] = vector3_t{ ances , 1.f, 0.f };
            g_server->send(true, liste, g_server->local_player.netid, -1);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (savetitle) {
            title_();
            return true;
        }
        break;
    }
    case fnv32("OnSendToServer"): g_server->redirect_server(varlist); return true;
    case fnv32("OnConsoleMessage"): {
        auto& cnsl = varlist[1].get_string();
        auto wry = varlist[1].get_string();

        if (son && wry.find("`6>>`4Spam detected! ``Please wait a bit before typing anything else.  Please note, any form of bot/macro/auto-paste will get all your accounts banned, so don't do it!") != -1) {
            variantlist_t varlist2{ "OnAddNotification" };
            varlist2[1] = 0;
            varlist2[2] = "`2Spam Stopped because spam detected!";
            varlist2[3] = 0;
            varlist2[4] = 0;
            g_server->send(true, varlist2);
            son = false;
            go_mode = false;

        }
        if (wry.find("World Lock``.``") != -1) {
            compresswltodl();
            return true;
        }
        gameupdatepacket_t pkt{};
        pkt.m_type = PACKET_ITEM_ACTIVATE_OBJECT_REQUEST;
        if (pkt.m_int_data > 112) {
            gt::send_log("Collected " + to_string(pkt.m_count) + " gems");
            return true;
        }
        if (cnsl.find("World Lock``.``") != -1) {
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("Collecteditems.txt");
                vw << cnsl + "\n";
                vw.close();
            }
            vr >> cnsl;
            vr.close();
            return true;
        }
        if (cnsl.find("Diamond Lock``.``") != -1) {
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("Collecteditems.txt");
                vw << cnsl + "\n";
                vw.close();
            }
            vr >> cnsl;
            vr.close();
            return true;
        }
        if (cnsl.find("Blue Gem Lock``.``") != -1) {
            std::ifstream vr;
            if (!vr) {
                std::ofstream vw;
                vw.open("Collecteditems.txt");
                vw << cnsl + "\n";
                vw.close();
            }
            vr >> cnsl;
            vr.close();
            return true;
        }
        if (gaspull) {
            if (wry.find("gas") != -1) {
                if (wry.find("`w") != -1) {
                    std::string nasmasma = wry.substr(wry.find("[W]_ `6<`w") + 10, wry.length() - wry.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/pull " + nasmasma);
                }
            }
        }
        varlist[1] = "`b[dsc.gg/visual-proxy]`` " + varlist[1].get_string();
        g_server->send(true, varlist);
        return true;
    }break;
    case fnv32("OnTalkBubble"): {
        auto wry = varlist[2].get_string();

        auto str = varlist[2].get_string();
        auto netid = varlist[1].get_int32();
        auto& bruh = g_server->m_world.local;
        auto cnsl = varlist[1].get_string();
        if (banscam == true) {
            g_server->send(true, varlist);
            if (autobanfire == true) {
                if (cnsl.find("`7[```4MWAHAHAHA!! FIRE FIRE FIRE") != -1) {
                    g_server->send(false, "action|wrench\n|netid|" + std::to_string(netid));
                    g_server->send(false, "action|dialog_return\ndialog_name|popup\nnetID|" + std::to_string(netid) + "|\nnetID|" + std::to_string(netid) + "|\nbuttonClicked|worldban");
                    return true;
                }
            }
            if (cnsl.find("Skem") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("scam") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("dont") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("Scam") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("SCam") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("noob") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("lol") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            else if (cnsl.find("LOL") != -1) {
                if (cnsl.find("`w") != -1) {
                    std::string nasmasma = cnsl.substr(cnsl.find("[W]_ `6<`w") + 10, cnsl.length() - cnsl.find("[W]_ `6<`w") - 1);
                    nasmasma.erase(nasmasma.begin() + nasmasma.find("``>``"), nasmasma.end());
                    g_server->send(false, "action|input\n|text|/ban " + nasmasma);
                }
            }
            return true;
        }
        if (g_server->m_world.name.find("city") != -1) {
            if (reme || qeme) {
                if (netid == g_server->m_world.local.netid)
                {
                    if (str.find("spun the wheel and got") != -1)
                    {
                        unaccess();
                        g_server->send(true, varlist);
                        return true;
                    }
                }
            }
        }
        if (netid == g_server->m_world.local.netid)
        {
            //gt::send_log("OnTalkBubble Detected on local player!");
            if (str.find("spun the wheel and got") != -1)
            {

                int playerx = bruh.pos.m_x / 32;
                int playery = bruh.pos.m_y / 32;
                std::string got = wry.substr(wry.find("spun the wheel and got ") + 25, wry.length());
                int the_num = std::atoi(got.substr(0, got.find(" ")).c_str());
                int toplam = 0;

                if (remee) {
                    switch (the_num) {
                    case 0:
                        toplam = 0;

                        break;
                    case 1:
                        toplam = 1;
                        break;
                    case 2:
                        toplam = 2;
                        break;
                    case 3:
                        toplam = 3;
                        break;
                    case 4:
                        toplam = 4;
                        break;
                    case 5:
                        toplam = 5;
                        break;
                    case 6:
                        toplam = 6;
                        break;
                    case 7:
                        toplam = 7;
                        break;
                    case 8:
                        toplam = 8;
                        break;
                    case 9:
                        toplam = 9;
                        break;
                    case 10:
                        toplam = 1;
                        break;
                    case 11:
                        toplam = 2;
                        break;
                    case 12:
                        toplam = 3;
                        break;
                    case 13:
                        toplam = 4;
                        break;
                    case 14:
                        toplam = 5;
                        break;
                    case 15:
                        toplam = 6;
                        break;
                    case 16:
                        toplam = 7;
                        break;
                    case 17:
                        toplam = 8;
                        break;
                    case 18:
                        toplam = 9;
                        break;
                    case 19:
                        toplam = 0;
                        break;
                    case 20:
                        toplam = 2;
                        break;
                    case 21:
                        toplam = 3;
                        break;
                    case 22:
                        toplam = 4;
                        break;
                    case 23:
                        toplam = 5;
                        break;
                    case 24:
                        toplam = 6;
                        break;
                    case 25:
                        toplam = 7;
                        break;
                    case 26:
                        toplam = 8;
                        break;
                    case 27:
                        toplam = 9;
                        break;
                    case 28:
                        toplam = 0;
                        break;
                    case 29:
                        toplam = 1;
                        break;
                    case 30:
                        toplam = 3;
                        break;
                    case 31:
                        toplam = 4;
                        break;
                    case 32:
                        toplam = 5;
                        break;
                    case 33:
                        toplam = 6;
                        break;
                    case 34:
                        toplam = 7;
                        break;
                    case 35:
                        toplam = 8;
                        break;
                    case 36:
                        toplam = 9;
                        break;
                    }
                }
                else if (qqe) {
                    switch (the_num) {
                    case 0:
                        toplam = 0;

                        break;
                    case 1:
                        toplam = 1;
                        break;
                    case 2:
                        toplam = 2;
                        break;
                    case 3:
                        toplam = 3;
                        break;
                    case 4:
                        toplam = 4;
                        break;
                    case 5:
                        toplam = 5;
                        break;
                    case 6:
                        toplam = 6;
                        break;
                    case 7:
                        toplam = 7;
                        break;
                    case 8:
                        toplam = 8;
                        break;
                    case 9:
                        toplam = 9;
                        break;
                    case 10:
                        toplam = 0;
                        break;
                    case 11:
                        toplam = 1;
                        break;
                    case 12:
                        toplam = 2;
                        break;
                    case 13:
                        toplam = 3;
                        break;
                    case 14:
                        toplam = 4;
                        break;
                    case 15:
                        toplam = 5;
                        break;
                    case 16:
                        toplam = 6;
                        break;
                    case 17:
                        toplam = 7;
                        break;
                    case 18:
                        toplam = 8;
                        break;
                    case 19:
                        toplam = 9;
                        break;
                    case 20:
                        toplam = 0;
                        break;
                    case 21:
                        toplam = 1;
                        break;
                    case 22:
                        toplam = 2;
                        break;
                    case 23:
                        toplam = 3;
                        break;
                    case 24:
                        toplam = 4;
                        break;
                    case 25:
                        toplam = 5;
                        break;
                    case 26:
                        toplam = 6;
                        break;
                    case 27:
                        toplam = 7;
                        break;
                    case 28:
                        toplam = 8;
                        break;
                    case 29:
                        toplam = 9;
                        break;
                    case 30:
                        toplam = 0;
                        break;
                    case 31:
                        toplam = 1;
                        break;
                    case 32:
                        toplam = 2;
                        break;
                    case 33:
                        toplam = 3;
                        break;
                    case 34:
                        toplam = 4;
                        break;
                    case 35:
                        toplam = 5;
                        break;
                    case 36:
                        toplam = 6;
                        break;
                    }
                }




            }
        }
        int toplam = 0;
        if (wry.find("spun the wheel and got") != -1)
        {
            int playerx = bruh.pos.m_x / 32;
            int playery = bruh.pos.m_y / 32;
            std::string got = wry.substr(wry.find("spun the wheel and got ") + 25, wry.length());
            int the_num = std::atoi(got.substr(0, got.find(" ")).c_str());
            if (remee) {
                switch (the_num) {
                case 0:
                    toplam = 0;

                    break;
                case 1:
                    toplam = 1;
                    break;
                case 2:
                    toplam = 2;
                    break;
                case 3:
                    toplam = 3;
                    break;
                case 4:
                    toplam = 4;
                    break;
                case 5:
                    toplam = 5;
                    break;
                case 6:
                    toplam = 6;
                    break;
                case 7:
                    toplam = 7;
                    break;
                case 8:
                    toplam = 8;
                    break;
                case 9:
                    toplam = 9;
                    break;
                case 10:
                    toplam = 1;
                    break;
                case 11:
                    toplam = 2;
                    break;
                case 12:
                    toplam = 3;
                    break;
                case 13:
                    toplam = 4;
                    break;
                case 14:
                    toplam = 5;
                    break;
                case 15:
                    toplam = 6;
                    break;
                case 16:
                    toplam = 7;
                    break;
                case 17:
                    toplam = 8;
                    break;
                case 18:
                    toplam = 9;
                    break;
                case 19:
                    toplam = 0;
                    break;
                case 20:
                    toplam = 2;
                    break;
                case 21:
                    toplam = 3;
                    break;
                case 22:
                    toplam = 4;
                    break;
                case 23:
                    toplam = 5;
                    break;
                case 24:
                    toplam = 6;
                    break;
                case 25:
                    toplam = 7;
                    break;
                case 26:
                    toplam = 8;
                    break;
                case 27:
                    toplam = 9;
                    break;
                case 28:
                    toplam = 0;
                    break;
                case 29:
                    toplam = 1;
                    break;
                case 30:
                    toplam = 3;
                    break;
                case 31:
                    toplam = 4;
                    break;
                case 32:
                    toplam = 5;
                    break;
                case 33:
                    toplam = 6;
                    break;
                case 34:
                    toplam = 7;
                    break;
                case 35:
                    toplam = 8;
                    break;
                case 36:
                    toplam = 9;
                    break;
                }
            }
            else if (qqe) {
                switch (the_num) {
                case 0:
                    toplam = 0;

                    break;
                case 1:
                    toplam = 1;
                    break;
                case 2:
                    toplam = 2;
                    break;
                case 3:
                    toplam = 3;
                    break;
                case 4:
                    toplam = 4;
                    break;
                case 5:
                    toplam = 5;
                    break;
                case 6:
                    toplam = 6;
                    break;
                case 7:
                    toplam = 7;
                    break;
                case 8:
                    toplam = 8;
                    break;
                case 9:
                    toplam = 9;
                    break;
                case 10:
                    toplam = 0;
                    break;
                case 11:
                    toplam = 1;
                    break;
                case 12:
                    toplam = 2;
                    break;
                case 13:
                    toplam = 3;
                    break;
                case 14:
                    toplam = 4;
                    break;
                case 15:
                    toplam = 5;
                    break;
                case 16:
                    toplam = 6;
                    break;
                case 17:
                    toplam = 7;
                    break;
                case 18:
                    toplam = 8;
                    break;
                case 19:
                    toplam = 9;
                    break;
                case 20:
                    toplam = 0;
                    break;
                case 21:
                    toplam = 1;
                    break;
                case 22:
                    toplam = 2;
                    break;
                case 23:
                    toplam = 3;
                    break;
                case 24:
                    toplam = 4;
                    break;
                case 25:
                    toplam = 5;
                    break;
                case 26:
                    toplam = 6;
                    break;
                case 27:
                    toplam = 7;
                    break;
                case 28:
                    toplam = 8;
                    break;
                case 29:
                    toplam = 9;
                    break;
                case 30:
                    toplam = 0;
                    break;
                case 31:
                    toplam = 1;
                    break;
                case 32:
                    toplam = 2;
                    break;
                case 33:
                    toplam = 3;
                    break;
                case 34:
                    toplam = 4;
                    break;
                case 35:
                    toplam = 5;
                    break;
                case 36:
                    toplam = 6;
                    break;
                }
            }
            if (packet->m_int_data == 1800)
            {
                if (remee)
                    varlist[2] = "`w " + wry + " `4REME: `b" + std::to_string(toplam);
                if (qqe)
                    varlist[2] = "`w " + wry + " `4QQ: `b" + std::to_string(toplam);
                varlist[2] = "`2[REAL]```` " + varlist[2].get_string();
                g_server->send(true, varlist);
                return true;
            }
            else {
                varlist[2] = varlist[2].get_string() + "`4[FAKE]````  ";
                g_server->send(true, varlist);
                return true;
            }
        }


        g_server->send(true, varlist);
        return true;
    } break;
    case fnv32("OnDialogRequest"): {
        auto content = varlist[1].get_string();
        if (dropwl == true) {
            if (content.find("Drop") != -1) {
                dropwl = false;
                return true;
            }
        }
        if (autobgl) {
            if (content.find("Dial a number to call somebody in Growtopia.") != -1) {
                int x = std::stoi(content.substr(content.find("embed_data|tilex|") + 17, content.length() - content.find("embed_data|tilex|") - 1));
                int y = std::stoi(content.substr(content.find("embed_data|tiley|") + 17, content.length() - content.find("embed_data|tiley|") - 1));
                g_server->send(false, "action|dialog_return\ndialog_name|phonecall\ntilex|" + to_string(x) + "|\ntiley|" + to_string(y) + "|\nnum|-2|\ndial|53785");
                return true;
            }
            if (autobgl) {
                if (content.find("embed_data|num|53785") != -1) {
                    int x = std::stoi(content.substr(content.find("embed_data|tilex|") + 17, content.length() - content.find("embed_data|tilex|") - 1));
                    int y = std::stoi(content.substr(content.find("embed_data|tiley|") + 17, content.length() - content.find("embed_data|tiley|") - 1));
                    g_server->send(false, "action|dialog_return\ndialog_name|phonecall\ntilex|" + to_string(x) + "|\ntiley|" + to_string(y) + "|\nnum|53785|\nbuttonClicked|chc5");
                    return true;
                }
            }
        }
        if (unaccessing == true) {
            if (content.find("unaccess") != -1) {
                unaccessing = false;
                return true;
            }
        }
        if (cdrop == true) {
            if (content.find("Drop") != -1) {
                cdrop = false;
                return true;
            }
        }
        else if (dropdl == true) {
            if (content.find("Drop") != -1) {
                dropdl = false;
                return true;
            }
        }
        else if (dropbgl == true) {
            if (content.find("Drop") != -1) {
                dropbgl = false;
                return true;
            }
        }

        if (content.find("add_label_with_icon|big|`wThe Growtopia Gazette``|left|5016|") != -1)
        {
            std::string paket = "add_label_with_icon|big|Welcome To Visual Proxy Gazette``|left|1460|"

                
                "\nadd_spacer|small"


                "\nadd_url_button||`1Join our discord server ``|NOFLAGS|https://discord.gg/aqkhTScxnK|"



                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2New Commands|left|826|"
                "\nadd_smalltext|`9Command : `2/find [keyword] `#(toggles items names, id)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fakeban `#(Fake Suspend)|left|2480|"
                "\nadd_smalltext|`9Command : `2/warn [text] `#(Custom Warning)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gems `#(See how many gems in world)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gs `#(Free Growscan)|left|2480|"
                "\nadd_smalltext|`9Command : `2/autobgl `#(toggles auto make bgl on/off)|left|2480|"
                "\nadd_smalltext|`9Command : `2/discord `#(Shows Button/Link to Discord Server)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fireban `#(Bans Pepole who put fire in world|left|2480|"



                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Visual Commands|left|2450|"
                "\nadd_smalltext|`9Command : `2/find [keyword] `#(toggles items names, id)|left|2480|"
                "\nadd_smalltext|`9Command : `2/legend `#(Enables Legendary Titles)|left|2480|"
                "\nadd_smalltext|`9Command : `2/mentor `#(Enables Mentor Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/g4g `#(Enables Grow4Good Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/maxlevel `#(Enables Blue Name Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/caitriona `#(Enables @Caitriona Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/seth `#(Enables @Seth Title)|left|2480|"
                "\nadd_smalltext|`9Command : `2/name [Any Name] `#(toggles Any Visual Name)|left|2480|"







                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Casino / Hosting Commands|left|758|"
                "\nadd_smalltext|`9Command : `2/pos1 `#(sets player(1) position)|left|2480|"
                "\nadd_smalltext|`9Command : `2/pos2 `#(sets player(2) position)|left|2480|"
                "\nadd_smalltext|`9Command : `2/win1 `#(teleports to player[1])|left|2480|"
                "\nadd_smalltext|`9Command : `2/win2 `#(teleports to player[2])|left|2480|"
                "\nadd_smalltext|`9Command : `2/mode `#[amount] (select game mode (No tax))|left|2480|"
                "\nadd_smalltext|`9Command : `2/game `#[amount] (Counts tax by 10%)|left|2480|"
                "\nadd_smalltext|`9Command : `2/tp `#(Start Auto host)|left|2480|"
                "\nadd_smalltext|`9Command : `2/gp `#(Pulls Everyone Who say Gas)|left|2480|"

                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Spam Commands|left|528|"
                "\nadd_smalltext|`9Command : `2/spam `#(toggles the spam page)|left|2480|"
                "\nadd_smalltext|`9Command : `2// `#(enables / disables spam)|left|2480|"

                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Dropping Commands|left|5480|"
                "\nadd_smalltext|`9Command : `2/dropwl [ammount] `#(Drops [ammount] wls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/dropbgl [amount] `#(Drops [ammount] bgls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/cd `#(custom drop)|left|2480|"
                "\nadd_smalltext|`9Command : `2/dd `#(Drops [ammount] dls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/daw `#(Drops all wls dls bgls)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fd `#(Enables Fast Drop)|left|2480|"
                "\nadd_smalltext|`9Command : `2/ft `#(Enables Fast Trash)|left|2480|"




                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Surg Commands|left|1258|"
                "\nadd_smalltext|`9Command : `2/autosurg `#(enables Autosurg)|left|2480|"


                "\nadd_spacer|small"
                "\nadd_label_with_icon|big|`2Other Commands|left|1674|"
                "\nadd_smalltext|`9Command : `2/flow `#(Warps to newest Team Flow Link!)|left|2480|"
                "\nadd_smalltext|`9Command : `2/discord `#(Shows Button/Link to Discord Server)|left|2480|"
                "\nadd_smalltext|`9Command : `2/options `#(toggles options page)|left|2480|"
                "\nadd_smalltext|`9Command : `2/autoban `#(bans everyone who joins world)|left|2480|"
                "\nadd_smalltext|`9Command : `2/fireban `#(Bans Pepole who put fire in world|left|2480|"
                "\nadd_smalltext|`9Command : `2/wrench `#(Wrench Mode, Enable / Disable / Change)|left|2480|"
                "\nadd_smalltext|`9Command : `2/world `#(toggles world options)|left|2480|"
                "\nadd_smalltext|`9Command : `2/blink `#(enables blink mode)|left|2480|"
                "\nadd_smalltext|`9Command : `2/mods `#(See if any mods are online)|left|2480|"
                "\nadd_smalltext|`9Command : `2/count `#[Amount] (Adjust Fast Drop Mode Count)|left|2480|"
                "\nadd_smalltext|`9Command : `2/countrylist `#(shows all country's flag id's)|left|2480|"
                "\nadd_smalltext|`9Command : `2/flag `#[country id] (changes your country flag [visable for everyone])|left|2480|"
                "\nadd_smalltext|`9Command : `2/pullall `#(Pulls everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/kickall `#(Kicks everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/banall `#(Bans everyone in the world At once)|left|2480|"
                "\nadd_smalltext|`9Command : `2/tradeall `#(Trades everyone in the world At once)|left|2480|"

                //"\nadd_label_with_icon|small|" + first + "/autosurg " + second + "(Enables Auto Surgery)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/balance " + second + "(Check your balance)|left|482|"

               // "\nadd_label_with_icon|small|" + first + "/gomode " + second + "(enables go mode)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/sendmsg " + second + "(send msg too people in list)|left|482|"
                //"\nadd_label_with_icon|small|" + first + "/give [item id] " + second + "(adds visual stuff to inventory)|left|482|"

              //  "\nadd_label_with_icon|small|" + first + "/speed " + second + "(Sellect speed)|left|482)|"


                //"\nadd_label_with_icon|small|" + first + "/mod -> " + second + "enables mod detect setting|left|2246|"


                //"\nadd_label_with_icon|small|" + first + "/warp [world name] " + second + "(warps to world of your choosen just like a supporter)|left|482|"
               // "\nadd_label_with_icon|small|" + first + "/inventory " + second + "(Displays inventory items id, count, name)|left|482|"
                "\nadd_quick_exit|"
                "\nset_survey_enabled|1"
                "\nend_dialog|gazette||OK|";
            varlist[1] = paket;
            g_server->send(true, varlist);
            return true;
        }
        if (auto_surg) {
            if (content.find("Edit") != -1) {
                wrenchx = atoi(content.substr(content.find("embed_data|tilex|") + 17, content.length() - content.find("embed_data|tilex|") - 1).c_str());
                wrenchy = atoi(content.substr(content.find("embed_data|tiley|") + 17, content.length() - content.find("embed_data|tiley|") - 1).c_str());
            }
            if (content.find("perform surgery") != -1)
            {
                used_sponge = false;
                if (content.find("Low Supply Warning:") != -1) {
                    gt::send_log("`4Deficient Tools.``");
                    return true;
                }

                std::string x = content.substr(content.find("embed_data|tilex|") + 17, content.length() - content.find("embed_data|tilex|") - 1);
                std::string y = content.substr(content.find("embed_data|tiley|") + 17, content.length() - content.find("embed_data|tiley|") - 1);
                wrenchx = 0;
                wrenchy = 0;
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                g_server->send(false, "action|dialog_return\ndialog_name|surge\ntilex|" + x + "|\ntiley|" + y + "|");
                return true;
            }
            if (content.find("end_dialog|surgery") != -1) {

                std::string x_status = content.substr(content.find("Status: ") + 8, content.length());
                std::string status = x_status.substr(0, x_status.find("|"));

                std::string x_pulse = content.substr(content.find("Pulse: ") + 7, content.length());
                std::string pulse = x_pulse.substr(0, x_pulse.find(" "));

                std::string x_temp = content.substr(content.find("Temp: ") + 8, content.length());
                int temp = std::atoi(x_temp.substr(0, x_temp.find(" ")).c_str());

                std::string x_inc = content.substr(content.find("Incisions: ") + 11, content.length());
                std::string inc = x_inc.substr(0, x_inc.find(" "));

                if (content.find("`4You can't see what you are doing!") != -1 && content.find("|noflags|1262|") == string::npos) {
                    sel.push_back(std::thread(send_tool, 1258, content));
                    return true;
                }
                if (content.find("`4Heart") != -1) {
                    sel.push_back(std::thread(send_tool, 4312, content));
                    return true;
                }
                if (content.find("The patient has not been diagnosed.") != -1)
                {
                    if (content.find("Patient is losing blood `4very quickly!") != -1 || content.find("Patient is `6losing blood!") != -1 || content.find("Patient is losing blood `3slowly.") != -1) //removed slowly cuz waste of tools
                    {
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }
                }
                if (content.find("flu.") != -1 && temp > 99) {
                    if (content.find("|noflags|1266|") != -1) sel.push_back(std::thread(send_tool, 1266, content));
                    else sel.push_back(std::thread(send_tool, 4318, content));
                    return true;
                }
                if (content.find("The patient has not been diagnosed.") == std::string::npos) {
                    if (content.find("Patient broke his leg.") != -1)
                    {
                        if (status.find("3Awake") != -1 || status.find("6Coming") != -1 || status.find("4Awake") != -1)
                        {
                            sel.push_back(std::thread(send_tool, 1262, content));
                            return true;
                        }
                    }
                    if (content.find("Patient had a heart attack.") != -1 || content.find("Patient wants a nose job.") != -1 || content.find("Patient has a tumor in their lung.") != -1 || content.find("Patient's spine is damaged.") != -1 || content.find("Patient has swallowed a world lock.") != -1)
                    {
                        if (status.find("4Awake") != -1)
                        {
                            sel.push_back(std::thread(send_tool, 1262, content));
                            return true;
                        }
                    }
                    else {
                        if (status.find("6Coming") != -1 && inc.find("`61") == std::string::npos || status.find("4Awake") != -1) {
                            sel.push_back(std::thread(send_tool, 1262, content));
                            return true;
                        }
                    }
                }
                if (temp > 99)
                {
                    if (content.find("|noflags|1266|") != -1) sel.push_back(std::thread(send_tool, 1266, content));
                    else sel.push_back(std::thread(send_tool, 4318, content));
                    return true;
                }
                if (pulse.find("Weak") != -1 || pulse.find("Extreme") != -1) {
                    sel.push_back(std::thread(send_tool, 4310, content));
                    return true;
                }
                if (content.find("is becoming hard to see your work") != -1 && !used_sponge) {
                    used_sponge = true;
                    sel.push_back(std::thread(send_tool, 1258, content));
                    return true;
                }
                if (content.find("The patient has not been diagnosed.") != -1) {
                    if (content.find("|noflags|4316|") != -1) {
                        sel.push_back(std::thread(send_tool, 4316, content));
                        return true;
                    }
                }
                if (inc.find("`3") != -1)
                {
                    if (content.find("Not sanitized") != -1 || content.find("Unsanitary") != -1 || content.find("Unclean") != -1) sel.push_back(std::thread(send_tool, 1264, content));
                    else sel.push_back(std::thread(send_tool, 1260, content));
                    return true;
                }
                //sickness under
                if (content.find("You've opened the skull.") != -1 || content.find("You removed the gravel!") != -1 || content.find("You repaired it.") != -1 || content.find("You cauterized it.") != -1 || content.find("You grafted in some nice new arteries!") != -1 || content.find("Patient suffered massive trauma with internal bleeding.") != -1)
                {
                    if (content.find("losing blood") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }
                }
                if (content.find("You removed the gravel!") != -1 || content.find("fixed the patient's feet") != -1 || content.find("replaced the patient's angr") != -1 || content.find("You repaired it.") != -1 || content.find("opened the abdomen") != -1 || content.find("You cauterized it.") != -1)
                {
                    if (inc.find("`6") != -1)
                    {
                        if (content.find("shattered") != -1)
                        {
                            sel.push_back(std::thread(send_tool, 4308, content));
                            return true;
                        }
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }
                    if (inc.find("`2") != -1 && content.find("broken``") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1268, content));
                        return true;
                    }

                }
                if (content.find("Patient broke his leg.") != -1)
                {
                    if (content.find("broken``") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1268, content));
                        return true;
                    }
                    if (inc.find("`20") != -1)
                    {
                        if (content.find("Not sanitized") != -1 || content.find("Unsanitary") != -1 || content.find("Unclean") != -1) sel.push_back(std::thread(send_tool, 1264, content));
                        else sel.push_back(std::thread(send_tool, 1260, content));
                        return true;
                    }
                    if (content.find("shattered``") != -1 && content.find("noflags|4308|") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 4308, content));
                        return true;
                    }
                    if (inc.find("`21") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }

                }
                if (content.find("Patient broke his arm.") != -1)
                {
                    if (content.find("broken``") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1268, content));
                        return true;
                    }
                    if (content.find("You splinted a broken bone") != -1 && content.find("Bones:") == std::string::npos && content.find("|noflags|1270|") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }
                }
                if (content.find("You rearranged their face!") != -1)
                {
                    sel.push_back(std::thread(send_tool, 1270, content));
                    return true;
                }
                if (content.find("exposed the angriest of teeth") != -1 || content.find("examined the wounds") != -1 || content.find("investigated the feet") != -1 || content.find("suffering from Moldy Guts") != -1 || content.find("accessed the arm muscles") != -1 || content.find("You found the lung puncture.") != -1 || content.find("You've finally found the tumor!") != -1 || content.find("You found the internal bleed.") != -1 || content.find("You've found gravel in the knees.") != -1 || content.find("You've opened the skull.") != -1 || content.find("The heart is now exposed for operating.") != -1 || content.find("You have cut into the nasal area.") != -1 || content.find("The lungs are now exposed.") != -1 || content.find("You've accessed the liver.") != -1 || content.find("You now have access to the appendix.") != -1 || content.find("You've opened up the vertebrae.") != -1 || content.find("You've opened the stomach.") != -1 || content.find("You now have access to the bad kidney.") != -1)
                {
                    if (inc.find("`2") != -1 && content.find("|noflags|1296|") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 1296, content));
                        return true;
                    }
                }
                if (content.find("Patient suffers from appendicitis.") != -1 || content.find("You got the lock out!") != -1 || content.find("You yanked out the appendix!") != -1 || content.find("You now have access to the appendix.") != -1 || content.find("You've opened up the vertebrae.") != -1 || content.find("You've opened the stomach.") != -1 || content.find("You excised the tumor!") != -1 || content.find("You treated the source of the infection!") != -1 || content.find("The lungs are now exposed.") != -1 || content.find("You've accessed the liver.") != -1 || content.find("The heart is now exposed for operating.") != -1 || content.find("You've found gravel in the knees.") != -1 || content.find("You found the internal bleed.") != -1 || content.find("You found the lung puncture.") != -1 || content.find("You've finally found the tumor!") != -1)
                {
                    if (content.find("losing blood") != -1)
                    {
                        sel.push_back(std::thread(send_tool, 4314, content));
                        return true;
                    }
                }
                if (content.find("the gem cuts closed") != -1 || content.find("You patched the torn punching") != -1 || content.find("You got the lock out!") != -1 || content.find("You yanked out the appendix!") != -1 || content.find("You popped in a fresh new kidney!") != -1 || content.find("You repaired the disc!") != -1 || content.find("You excised the tumor!") != -1 || content.find("You treated the source of the infection!") != -1 || content.find("You rearranged their face!") != -1 || content.find("You grafted in some nice new arteries!") != -1 || content.find("You reduced the swelling!") != -1) {
                    if (inc.find("`6") != -1) {
                        sel.push_back(std::thread(send_tool, 1270, content));
                        return true;
                    }
                }
                if (inc.find("`20") != -1 && content.find("losing blood") != -1)
                {
                    sel.push_back(std::thread(send_tool, 1270, content));
                    return true;
                }
                if (content.find("s fever is") != -1)
                {
                    if (content.find("|noflags|1266|") != -1) sel.push_back(std::thread(send_tool, 1266, content));
                    else sel.push_back(std::thread(send_tool, 4318, content));
                    return true;
                }
            }
        }
        if (content.find("add_label_with_icon|big|`wTelephone``|left|3898") != -1) {
            if (autobgl == true) {
                g_server->send(false, "add_text_input|dial|Phone #|12345|5");
                g_server->send(false, "action|dialog_return\ndialog_name|phonecall\ntilex||\ntiley||\num|12345|\ndial|");
            }
        }
        if (wrench) {
            std::string bruhmomento = content.substr(content.find("embed_data|netID") + 17, content.length() - content.find("embed_data|netID") - 1);
            if (content.find("set_default_color|`o") != -1) {
                if (content.find("embed_data|netID") != -1) {
                    return true;
                }
            }
        }
        if (content.find("add_label_with_icon|big|`wVending Machine``|left|2978") != -1)
        {
            if (fastvend) {
                if (content.find("How many would you like to buy?") != -1) {
                    int x = std::stoi(content.substr(content.find("embed_data|tilex|") + 17, content.length() - content.find("embed_data|tilex|") - 1));
                    int y = std::stoi(content.substr(content.find("embed_data|tiley|") + 17, content.length() - content.find("embed_data|tiley|") - 1));
                    int itemid = std::stoi(content.substr(content.find("embed_data|expectitem|") + 22, content.length() - content.find("embed_data|expectitem|") - 1));
                    int expectprice = std::stoi(content.substr(content.find("embed_data|expectprice|") + 23, content.length() - content.find("embed_data|expectprice|") - 1));
                    int yourwl = std::stoi(content.substr(content.find("add_textbox|You have") + 20, content.length() - content.find("add_textbox|You have") - 1));
                    if (yourwl - expectprice < 0) {
                    }
                    else {
                        g_server->send(false, "action|dialog_return\ndialog_name|vending\ntilex|" + std::to_string(x) + "|\ntiley|" + std::to_string(y) + "|\nverify|1|\nbuycount|" + expectcount + "|\nexpectprice|" + std::to_string(expectprice) + "|\nexpectitem|" + std::to_string(itemid) + "|");
                        return true;
                    }
                }


            }

        }
        if (fastdrop) {
            if (dcount == "0") {
                std::string itemid = content.substr(content.find("embed_data|itemID|") + 18, content.length() - content.find("embed_data|itemID|") - 1);
                std::string count = content.substr(content.find("count||") + 7, content.length() - content.find("count||") - 1);
                if (content.find("embed_data|itemID|") != -1) {
                    if (content.find("Drop") != -1) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(300));
                        g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|" + itemid + "|\ncount|" + count);
                        return true;
                    }
                }
            }
            else {
                std::string itemid = content.substr(content.find("embed_data|itemID|") + 18, content.length() - content.find("embed_data|itemID|") - 1);
                g_server->send(false, "action|dialog_return\ndialog_name|drop_item\nitemID|" + itemid + "|\ncount|" + dcount);
                return true;
            }
        }
        if (fasttrash) {
            std::string itemid = content.substr(content.find("embed_data|itemID|") + 18, content.length() - content.find("embed_data|itemID|") - 1);
            std::string count = content.substr(content.find("you have ") + 9, content.length() - content.find("you have ") - 1);
            std::string delimiter = ")";
            std::string token = count.substr(0, count.find(delimiter));
            if (content.find("embed_data|itemID|") != -1) {
                if (content.find("Trash") != -1) {
                    g_server->send(false, "action|dialog_return\ndialog_name|trash_item\nitemID|" + itemid + "|\ncount|" + token);
                    return true;
                }
            }
        }
        else if (varlist[3].get_int32() == 276) {
            variantlist_t varlst{ "OnAddNotification" };
            varlst[1] = "interface/seth.rttex";
            varlst[2] = "`4GUARDIAN `7IS IN THIS WORLD";
            varlst[3] = "audio/already_used.wav";
            varlst[4] = 0;
            g_server->send(true, varlst);
            gt::send_log("`4Guardian`7 Entered The World.");
            g_server->send(false, "action|quit_to_exit", 3);
        }
    }break;

    case fnv32("OnRemove"): {
        auto text = varlist.get(1).get_string();
        if (text.find("netID|") == 0) {
            auto netid = atoi(text.substr(6).c_str());

            if (netid == g_server->m_world.local.netid) {
                g_server->m_world.local = {};
                g_server->m_world.objects.clear();


            }
            auto& players = g_server->m_world.players;
            for (size_t i = 0; i < players.size(); i++) {
                auto& player = players[i];
                if (player.netid == netid) {
                    players.erase(std::remove(players.begin(), players.end(), player), players.end());
                    break;
                }
            }
        }
    } break;
    case fnv32("OnSpawn"): {

        std::string meme = varlist.get(1).get_string();
        rtvar var = rtvar::parse(meme);
        auto name = var.find("name");
        auto netid = var.find("netID");
        auto onlineid = var.find("onlineID");
        if (name && netid && onlineid) {
            player ply{};
            ply.mod = false;
            ply.invis = false;
            ply.name = name->m_value;
            ply.country = var.get("country");
            name->m_values[0] += "";



            if (ply.name.substr(2).substr(0, ply.name.length() - 4) == "CityGrowtopia") {
                //std::this_thread::sleep_for(std::chrono::milliseconds(50));
                g_server->send(false, "action|input\n|text|Patron Hosgeldin! Kulo Proxy Best!");
            }
            if (enter_pull) {
                // std::this_thread::sleep_for(std::chrono::milliseconds(50));
                g_server->send(false, "action|input\n|text|/pull " + ply.name.substr(2).substr(0, ply.name.length() - 4));
            }
            if (enter_ban) {
                //  std::this_thread::sleep_for(std::chrono::milliseconds(50));
                g_server->send(false, "action|input\n|text|/ban " + ply.name.substr(2).substr(0, ply.name.length() - 4));
            }
            /*if (ply.name.substr(2).substr(0, ply.name.length() - 4) != g_server->m_world.local.name) {
                adamlar.push_back(ply.name.substr(2).substr(0, ply.name.length() - 4));
            }*/

            if (pullbynames == true) {

                // std::this_thread::sleep_for(std::chrono::milliseconds(50));
                g_server->send(false, "action|input\n|text|/pull " + vardaspull);
            }
            if (banbynames == true) {

                // std::this_thread::sleep_for(std::chrono::milliseconds(50));
                g_server->send(false, "action|input\n|text|/ban " + vardasban);

            }

            //catch (std::exception) { gt::send_log("Critical Error : Invalid String Position"); }
       // }
            auto pos = var.find("posXY");
            if (pos && pos->m_values.size() >= 2) {
                auto x = atoi(pos->m_values[0].c_str());
                auto y = atoi(pos->m_values[1].c_str());
                ply.pos = vector2_t{ float(x), float(y) };
            }
            ply.userid = var.get_int("userID");
            ply.netid = var.get_int("netID");
            if (meme.find("type|local") != -1) {
                //set mod state to 1 (allows infinite zooming, this doesnt ban cuz its only the zoom not the actual long punch)
                var.find("mstate")->m_values[0] = "1";
                g_server->m_world.local = ply;
                if (antigravity) anti_gravity();

                blockfirst = true;
            }
            g_server->m_world.players.push_back(ply);
            auto str = var.serialize();
            utils::replace(str, "onlineID", "onlineID|");
            varlist[1] = str;
            //PRINTC("new: %s\n", varlist.print().c_str());
            g_server->send(true, varlist, -1, -1);
            return true;
        }
    } break;
    case fnv32("OnSetPos"): {
        if (gt::noclip)
            return true;
        return false;
    }
    case fnv32("OnNameChanged"): std::thread(itsmod, packet->m_player_flags, varlist[1].get_string()).detach(); return false;
    }
    return false;
};
bool events::in::generictext(std::string packet) {
    if (iswear) send_vset();
    return false;
}

bool events::in::gamemessage(std::string packet) {

    if (gt::resolving_uid2) {
        if (packet.find("PERSON IGNORED") != -1) {
            g_server->send(false, "action|dialog_return\ndialog_name|friends_guilds\nbuttonClicked|showfriend");
            g_server->send(false, "action|dialog_return\ndialog_name|friends\nbuttonClicked|friend_all");
        }
        else if (packet.find("Nobody is currently online with the name") != -1) {
            gt::resolving_uid2 = false;
            gt::send_log("Target is offline, cant find uid.");
        }
        else if (packet.find("Clever perhaps") != -1) {
            gt::resolving_uid2 = false;
            gt::send_log("Target is a moderator, can't ignore them.");
        }
    }
    return false;
}

bool events::in::sendmapdata(gameupdatepacket_t* packet, int packetLength) {
    g_server->m_world.LoadFromMem(packet);
    g_server->m_world.connected = true;
    return false;
}

bool events::in::state(gameupdatepacket_t* packet) {
    if (!g_server->m_world.connected)
        return false;
    if (packet->m_player_flags == -1)
        return false;

    auto& players = g_server->m_world.players;

    for (auto& player : players) {
        if (player.netid == packet->m_player_flags) {
            player.pos = vector2_t{ packet->m_vec_x, packet->m_vec_y };
            break;
        }
    }

    return false;
}

bool events::in::tracking(std::string packet) {
    PRINTC("Tracking packet: %s\n", packet.c_str());
    if (packet.find("eventName|102_PLAYER.AUTHENTICATION") != -1)
    {
        string wlbalance = packet.substr(packet.find("Worldlock_balance|") + 18, packet.length() - packet.find("Worldlock_balance|") - 1);

        if (wlbalance.find("PLAYER.") != -1)
        {
            gt::send_log("`9World Lock Balance: `#0");
        }
        else
        {
            gt::send_log("`9World Lock Balance: `#" + wlbalance);

        }
        if (packet.find("Authenticated|1") != -1)
        {
            gt::send_log("`9Player Authentication `2Successfuly.");
        }
        else
        {
            gt::send_log("`9Player Authentication `4Failed.");
        }

    }
    if (packet.find("eventName|100_MOBILE.START") != -1)
    {
        gems = packet.substr(packet.find("Gems_balance|") + 13, packet.length() - packet.find("Gems_balance|") - 1);
        level = packet.substr(packet.find("Level|") + 6, packet.length() - packet.find("Level|") - 1);
        uid = packet.substr(packet.find("GrowId|") + 7, packet.length() - packet.find("GrowId|") - 1);
        gt::send_log("`9Gems Balance: `#" + gems);
        gt::send_log("`9Account Level: `#" + level);
        gt::send_log("`9Your Current UID: `#" + uid);
    }
    if (packet.find("eventName|300_WORLD_VISIT") != -1)
    {
        if (packet.find("Locked|0") != -1)
        {
            gt::send_log("`4This world is not locked by a world lock.");
        }
        else
        {
            gt::send_log("`2This world is locked by a world lock.");

            if (packet.find("World_owner|") != -1)
            {
                string uidd = packet.substr(packet.find("World_owner|") + 12, packet.length() - packet.find("World_owner|") - 1);
                gt::send_log("`9World Owner UID: `#" + uidd);

            }
        }
    }

    return true;
}