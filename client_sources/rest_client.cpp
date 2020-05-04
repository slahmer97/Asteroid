
#include <client_message_factory.h>
#include "headers/rest_client.h"
#include "headers/graphiqueSDL.h"
#include "headers/polyClient.h"
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <game_shapes.h>

std::shared_ptr<rest_client> rest_client::s_rest_client;


void rest_client::init(std::string &host, std::string &port) {
    m_uri = std::string(host) + std::string(":") + std::string(port) + std::string("/echo");
}


void rest_client::client_network() {
    m_g_httpHandler = new WsClient(m_uri);
    m_g_httpHandler->on_message = [&](const std::shared_ptr<WsClient::Connection> connection,
                                      const std::shared_ptr<WsClient::InMessage> in_message) {
        this->on_message(connection, in_message);
    };

    m_g_httpHandler->on_open = [&](const std::shared_ptr<WsClient::Connection> connection) {
        this->on_open(connection);
    };

    m_g_httpHandler->on_close = [&](const std::shared_ptr<WsClient::Connection> connection, int status,
                                    const std::string &reason) {
        this->on_close(connection, status, reason);
    };

    m_g_httpHandler->on_error = [&](const std::shared_ptr<WsClient::Connection> connection,
                                    const SimpleWeb::error_code &ec) {
        this->on_error(connection, ec);
    };

    m_g_httpHandler->start();
}

[[noreturn]] void rest_client::client_gui() {
    graphiqueSDL fenetre{};

    std::thread events_polling([&]() {
        while (true) {
            auto start = std::chrono::steady_clock::now();

            std::vector<bool> ret = fenetre.getTouche();
            if (ret[0] == true) {
                send_move_forward_message();
            }
            if (ret[1] == true) {
                send_rotate_right_message();
            }
            if (ret[2] == true) {
                send_rotate_left_message();
            }
            if (ret[3] == true) {
                send_fire_message("X1");
            }
            if (ret[4] == true) {
                send_fire_message("X2");
            }
            if (ret[5] == true) {
                send_fire_message("X3");
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(70));
        }

    });

    std::vector<std::shared_ptr<polyClient>> v;

    while (true) {
        fenetre.update_keys();
        fenetre.clearImage();
        for (const auto &i : *game_shapes::get_shapes()) {
            if (i != nullptr)
                fenetre << *i;
        }
        game_shapes::get_score().afficherSurFenetre(fenetre);
        fenetre.afficherImage();
    }
}


void rest_client::run() {
    std::unique_ptr<std::thread> gui;
    std::unique_ptr<std::thread> net;

    std::string input;
    do {
        std::cout << "Enter a command : ";
        std::cin >> input;
        if (input == "start_net") {
            net = std::make_unique<std::thread>(std::thread([&]() {
                this->client_network();
            }));
        } else if (input == "start_gui") {
            gui = std::make_unique<std::thread>(std::thread([&]() {
                this->client_gui();
            }));
        } else if (input == "create_game") {
            send_create_game_message();
        } else if (input == "join_game") {
            send_join_game_message();
        } else if (input == "forward") {
            send_move_forward_message();
        } else if (input == "backward") {
            send_move_backward_message();
        } else if (input == "left") {
            send_rotate_left_message();
        } else if (input == "right") {
            send_rotate_right_message();
        } else if (input == "fire") {
            send_fire_message();
        } else if (input == "set_username") {
            std::string tmp;
            std::cout << "username : ";
            std::cin >> tmp;
            set_username(std::move(tmp));
        } else if (input == "set_game_id") {
            std::string tmp;
            std::cout << "game_id : ";
            std::cin >> tmp;
            set_game_id(std::move(tmp));
        } else if (input == "close") {
            std::cout << "Main loop ended\n";
            break;
        } else if (input == "s1j1" || input == "fast") {
            std::string t = "1";
            fast_config("salon1", "joueur1", gui, net, true, t);
        } else if (input == "s1j2") {
            std::string t = "2";
            fast_config("salon1", "joueur2", gui, net, false, t);
        } else if (input == "s2j1") {
            std::string t = "1";
            fast_config("salon2", "joueur1", gui, net, true, t);
        } else if (input == "s2j2") {
            std::string t = "1";
            fast_config("salon2", "joueur2", gui, net, false, t);
        } else {
            std::cout << "unknown command\n";
        }

    } while (true);


    if (gui != nullptr)
        gui->join();

}

void rest_client::fast_config(std::string &&salon, std::string &&joueur, std::unique_ptr<std::thread> &gui,
                              std::unique_ptr<std::thread> &net, bool creer_salon, std::string team) {
    int d = 500;
    std::cout << "username : " << joueur << std::endl;
    set_username(std::forward<std::string>(joueur));
    std::this_thread::sleep_for(std::chrono::milliseconds(d));
    std::cout << "game_id : " << salon << std::endl;
    set_game_id(std::forward<std::string>(salon));
    std::cout << "team : " << team << std::endl;
    set_team(std::move(team));
    std::this_thread::sleep_for(std::chrono::milliseconds(d));
    std::cout << "start_net" << std::endl;
    net = std::make_unique<std::thread>(std::thread([&]() {
        this->client_network();
    }));
    std::this_thread::sleep_for(std::chrono::milliseconds(d));
    if (creer_salon) {
        std::cout << "create_game" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(d));
        send_create_game_message();
    } else {
        std::cout << "join_game" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(d));
        send_join_game_message();
    }
    gui = std::make_unique<std::thread>(std::thread([&]() {
        this->client_gui();
    }));
}

std::shared_ptr<rest_client> rest_client::get_instance() noexcept {
    if (rest_client::s_rest_client == nullptr) {
        rest_client::s_rest_client = std::make_shared<rest_client>(rest_client());
        //BOOST_LOG_TRIVIAL(info)<<"rest client instance is being created";
    } else {
        //BOOST_LOG_TRIVIAL(warning)<<"rest client instance already exist";
    }
    return rest_client::s_rest_client;
}


std::string rest_client::send_message(const std::string &message) {
    if (this->m_connection == nullptr) {
        //BOOST_LOG_TRIVIAL(fatal)<<"Attempting to send message without specifiying server connection";
        throw std::runtime_error("server connection is null");
    }
    m_connection->send(message);
    return "DONE";
}


void rest_client::on_open(std::shared_ptr<WsClient::Connection> connection) {
    //BOOST_LOG_TRIVIAL(info)<<"on_open() start";

    //connection->send("Hello server");
    this->m_connection = connection;
    //BOOST_LOG_TRIVIAL(info)<<"on_open() end";

}

void rest_client::on_message(const std::shared_ptr<WsClient::Connection> connection,
                             const std::shared_ptr<WsClient::InMessage> in_message) {
    ////BOOST_LOG_TRIVIAL(info)<<"on_message() start";
    std::stringstream ss;
    ss << in_message->string();
    pt::ptree root;
    pt::read_json(ss, root);
    auto type = root.get<std::string>("type");
    if (type == "game_view") {
        // //BOOST_LOG_TRIVIAL(info)<<"received game view";
        std::vector<std::shared_ptr<polyClient>> objects;

        for (pt::ptree::value_type &shape : root.get_child("shapes")) {
            // fruit.first contain the string ""
            std::vector<vec2d> list;
            auto tmp_type = shape.second.get<std::string>("type");
            if (tmp_type == "polygone") {
                //      //BOOST_LOG_TRIVIAL(info)<<"-------- Found polygone -------";
                for (pt::ptree::value_type &cor : shape.second.get_child("points")) {
                    auto x = cor.second.get<std::string>("x");
                    auto y = cor.second.get<std::string>("y");
                    list.emplace_back(boost::lexical_cast<double>(x), boost::lexical_cast<double>(y));
                }
            }
            objects.push_back(std::make_shared<polyClient>(polyClient(list)));
        }
        game_shapes::emplace(std::move(objects));

    } else if (type == "infos") {
        auto s1 = root.get<std::string>("s1");
        auto s2 = root.get<std::string>("s2");
        auto x2 = root.get<std::string>("X2");
        auto x3 = root.get<std::string>("X3");
        game_shapes::update_score(x2, x3, s1, s2);
    } else if (type == "error") {
        BOOST_LOG_TRIVIAL(warning) << "received error";
    }
    else if(type == "end_of_game") {
        BOOST_LOG_TRIVIAL(warning) << "game ended : \n"<<ss.str();
    }
    else {
             BOOST_LOG_TRIVIAL(warning) << "not recognized";
             return;

     }
    //BOOST_LOG_TRIVIAL(info)<<"on_message() end";
}

void rest_client::on_error(const std::shared_ptr<WsClient::Connection> connection, const SimpleWeb::error_code &ec) {
    //BOOST_LOG_TRIVIAL(info)<<"on_error() start";


    //BOOST_LOG_TRIVIAL(info)<<"on_error() end";
}

void
rest_client::on_close(const std::shared_ptr<WsClient::Connection> connection, int status, const std::string &reason) {
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

void rest_client::send_fire_message(const std::string &type) {
    std::string msg = client_message_factory::get_fire_message(type);
    send_message(msg);
}

void rest_client::send_create_game_message() {
    //BOOST_LOG_TRIVIAL(info)<<"send_create_game_message()";
    std::string payload = client_message_factory::get_create_game_message(m_username, m_game_id, m_team);
    std::string ret = send_message(payload);
    //BOOST_LOG_TRIVIAL(info)<<"Reiceived : "<<ret;
}

void rest_client::send_join_game_message() {
    std::string msg = client_message_factory::get_join_game_message(m_game_id, m_username, m_team);
    send_message(msg);
}

void rest_client::set_username(std::string &&username) {
    m_username = username;
}

void rest_client::set_game_id(std::string &&game_id) {
    m_game_id = game_id;
}

void rest_client::set_team(std::string &&team) {
    m_team = team;
}