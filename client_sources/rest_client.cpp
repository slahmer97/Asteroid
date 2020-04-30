//
// Created by stevlulz on 08/04/2020.
//

#include <thread>
#include <client_message_factory.h>
#include "headers/rest_client.h"
#include "headers/graphiqueSDL.h"
#include "headers/polyClient.h"
#include "headers/client_http_service_handler.h"
#include "headers/alphaNumClient.h"
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <game_shapes.h>

std::shared_ptr<rest_client> rest_client::s_rest_client;


void rest_client::init(std::string &host, std::string &port) {
    //BOOST_LOG_TRIVIAL(info)<<"init() start";
    m_uri = std::string(host)+std::string(":")+std::string(port)+std::string("/echo");
    //BOOST_LOG_TRIVIAL(info)<<"init() uri is created : "<<m_uri;
    //BOOST_LOG_TRIVIAL(info)<<"init() exit";

}


void rest_client::client_network()  {
    //BOOST_LOG_TRIVIAL(info)<<"client_network() init "<<m_uri;
    m_g_httpHandler = new WsClient(m_uri);
    m_g_httpHandler->on_message = [&](const std::shared_ptr<WsClient::Connection>& connection, const std::shared_ptr<WsClient::InMessage> &in_message) {
        this->on_message(connection,in_message);
    };

    m_g_httpHandler->on_open = [&](const std::shared_ptr<WsClient::Connection>& connection) {
        this->on_open(const_cast<std::shared_ptr<WsClient::Connection> &>(connection));
    };

    m_g_httpHandler->on_close = [&](const std::shared_ptr<WsClient::Connection>& connection, int status, const std::string & reason) {
        this->on_close(connection,status,reason);
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    m_g_httpHandler->on_error = [&](const std::shared_ptr<WsClient::Connection>& connection, const SimpleWeb::error_code &ec) {
        this->on_error(connection,ec);
    };

    m_g_httpHandler->start();
    //BOOST_LOG_TRIVIAL(info)<<"client network interface is running on : "<<m_uri;
}

[[noreturn]] void rest_client::client_gui(){
    //main thread for displaying gui
    //BOOST_LOG_TRIVIAL(info)<<"client_gui() started";

    graphiqueSDL fenetre{};

    //A.emplace_back(new polyClient{ {200, 100}, {400, 300}, {500, 500}});
    //A.emplace_back(new alphaNumClient{"HelloWorld, le retour ! Score : 19999", {10,10}});
    std::thread events_polling([&](){
        while(true){
            auto start = std::chrono::steady_clock::now();
            /*
            std::string s = fenetre.getTouche(); // getTouche() ne bloque PAS le thread, elle renvoie "" si rien
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start );
            if (s == "") {}
            else if (s == "space") send_fire_message();
            else if (s == "up") send_move_forward_message();
            else if (s == "right"){ send_rotate_right_message();}
            else if (s == "left") send_rotate_left_message();
             */
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - start );

            std::vector<bool> ret = fenetre.getTouche();
            if(ret[0] == true){
                send_move_forward_message();
            }
            if(ret[1] == true){
                send_rotate_right_message();
            }
            if(ret[2] == true){
                send_rotate_left_message();
            }
            if(ret[3] == true){
                send_fire_message();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
         }

    });

    std::vector<std::shared_ptr<polyClient>> v;

    while (true) {
        fenetre.update_keys();
        fenetre.clearImage();
        for (const auto& i : *game_shapes::get_shapes()) {
            if(i != nullptr)
                i->afficherSurFenetre(fenetre);
            //else
                //BOOST_LOG_TRIVIAL(error)<<"client_gui() error";
        }
        fenetre.afficherImage();
    }
    //BOOST_LOG_TRIVIAL(info)<<"client_gui() ended";
}


void rest_client::run() {
    std::unique_ptr<std::thread> gui;
    std::unique_ptr<std::thread> net;

    std::string input;
    do{
        std::cout<<"Enter a command : ";
        std::cin>>input;
        if (input == "start_net"){
            net = std::make_unique<std::thread>(std::thread([&]() {
                //BOOST_LOG_TRIVIAL(info)<<"network thread started";
                this->client_network();
            }));
        }
        else if(input == "start_gui"){
            gui = std::make_unique<std::thread>(std::thread([&]() {
                //BOOST_LOG_TRIVIAL(info)<<"gui thread started";
                this->client_gui();
            }));
        }
        else if(input == "create_game"){
            send_create_game_message();
        }
        else if(input == "join_game"){
            send_join_game_message();
        }
        else if(input == "forward"){
            send_move_forward_message();
        }
        else if(input == "backward"){
            send_move_backward_message();
        }
        else if(input == "left"){
            send_rotate_left_message();
        }
        else if(input == "right"){
            send_rotate_right_message();
        }
        else if(input == "fire"){
            send_fire_message();
        }
        else if(input == "set_username"){
            std::string tmp;
            std::cout<<"username : ";
            std::cin>>tmp;
            set_username(std::move(tmp));
        }
        else if(input == "set_game_id"){
            std::string tmp;
            std::cout<<"game_id : ";
            std::cin>>tmp;
            set_game_id(std::move(tmp));
        }
        else if(input == "close"){
            std::cout<<"Main loop ended\n";
            break;
        }
        else if(input == "fast"){
            int d = 500;
            std::cout<<"username : fast1" << std::endl;
            set_username("fast1");
            std::this_thread::sleep_for(std::chrono::milliseconds(d));
            std::cout<<"game_id : gid" << std::endl;
            set_game_id("gid");
            std::this_thread::sleep_for(std::chrono::milliseconds(d));
            std::cout<<"start_net" << std::endl;
            net = std::make_unique<std::thread>(std::thread([&]() {
                //BOOST_LOG_TRIVIAL(info)<<"network thread started";
                this->client_network();
            }));
            std::this_thread::sleep_for(std::chrono::milliseconds(d));
            std::cout<<"create_game" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(d));
            send_create_game_message();
            gui = std::make_unique<std::thread>(std::thread([&]() {
                //BOOST_LOG_TRIVIAL(info)<<"gui thread started";
                this->client_gui();
            }));
        }
        else {
            std::cout<<"unknown command\n";
        }

    }while(true);


    if(gui != nullptr)
        gui->join();

}

std::shared_ptr<rest_client > rest_client::get_instance() noexcept {
    if (rest_client::s_rest_client == nullptr){
        rest_client::s_rest_client = std::make_shared<rest_client>(rest_client());
        //BOOST_LOG_TRIVIAL(info)<<"rest client instance is being created";
    }
    else{
        //BOOST_LOG_TRIVIAL(warning)<<"rest client instance already exist";
    }
    return rest_client::s_rest_client;
}


std::string rest_client::send_message(const std::string &message){
    if(this->m_connection == nullptr){
        //BOOST_LOG_TRIVIAL(fatal)<<"Attempting to send message without specifiying server connection";
        throw std::runtime_error("server connection is null");
    }
    m_connection->send(message);
    return "DONE";
}





void rest_client::on_open(std::shared_ptr<WsClient::Connection>& connection){
    //BOOST_LOG_TRIVIAL(info)<<"on_open() start";

    //connection->send("Hello server");
    this->m_connection = connection;
    //BOOST_LOG_TRIVIAL(info)<<"on_open() end";

}
void rest_client::on_message(const std::shared_ptr<WsClient::Connection>& connection,const std::shared_ptr<WsClient::InMessage>& in_message){
    ////BOOST_LOG_TRIVIAL(info)<<"on_message() start";
    std::stringstream ss;
    ss << in_message->string();
    pt::ptree root;
    pt::read_json(ss, root);
    auto type = root.get<std::string>("type");
    if(type == "game_view"){
       // //BOOST_LOG_TRIVIAL(info)<<"received game view";
        std::vector<std::shared_ptr<polyClient>> objects;

        for (pt::ptree::value_type &shape : root.get_child("shapes"))
        {
            // fruit.first contain the string ""
            std::vector<vec2d> list;
            auto tmp_type = shape.second.get<std::string>("type");
            if(tmp_type == "polygone"){
          //      //BOOST_LOG_TRIVIAL(info)<<"-------- Found polygone -------";
                for (pt::ptree::value_type &cor : shape.second.get_child("points")){
                    std::string x = cor.second.get<std::string>("x");
                    std::string y = cor.second.get<std::string>("y");
                    list.emplace_back(boost::lexical_cast<double>(x),boost::lexical_cast<double>(y));
                }
            }
            objects.push_back(std::make_shared<polyClient>(polyClient(list)));
        }
        game_shapes::emplace(std::move(objects));

    }
    else if(type == "error"){
        //BOOST_LOG_TRIVIAL(warning)<<"received error";
    }
    else{
        //BOOST_LOG_TRIVIAL(info)<<"received other thing";
    }
    //BOOST_LOG_TRIVIAL(info)<<"on_message() end";
}

void rest_client::on_error(const std::shared_ptr<WsClient::Connection> &connection, const SimpleWeb::error_code &ec) {
    //BOOST_LOG_TRIVIAL(info)<<"on_error() start";


    //BOOST_LOG_TRIVIAL(info)<<"on_error() end";
}

void rest_client::on_close(const std::shared_ptr<WsClient::Connection> &connection, int status, const std::string &reason) {
    //BOOST_LOG_TRIVIAL(info)<<"on_close() start";


    //BOOST_LOG_TRIVIAL(info)<<"on_close() end";
}

void rest_client::send_move_forward_message() {
    std::string msg = client_message_factory::get_move_forward_message();
    send_message(msg);
}

void rest_client::send_move_backward_message() {
    std::string msg = client_message_factory::get_move_backward_message();
    send_message(msg);
}

void rest_client::send_rotate_left_message() {
    std::string msg = client_message_factory::get_left_rotate_message();
    send_message(msg);
}

void rest_client::send_rotate_right_message() {
    std::string msg = client_message_factory::get_right_rotate_message();
    send_message(msg);
}

void rest_client::send_fire_message() {
    std::string msg = client_message_factory::get_fire_message();
    send_message(msg);
}
void rest_client::send_create_game_message(){
    //BOOST_LOG_TRIVIAL(info)<<"send_create_game_message()";
    std::string payload = client_message_factory::get_create_game_message(m_username,m_game_id);

    std::string ret = send_message(payload);

    //BOOST_LOG_TRIVIAL(info)<<"Reiceived : "<<ret;
}
void rest_client::send_join_game_message() {
    std::string msg = client_message_factory::get_join_game_message(m_game_id,m_username);
    send_message(msg);
}

void rest_client::set_username(std::string&& username){
    m_username = username;
}
void rest_client::set_game_id(std::string&& game_id){
    m_game_id = game_id;
}