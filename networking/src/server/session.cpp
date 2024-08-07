#include "server/session.h"

Session::Session(tcp::socket&& socket, const std::function<void(const User& user, const std::string& message)>& notifier) :
    TCP::Connection(std::move(socket), notifier) {}

void Session::start() {
    on_connect = [this]() {
        EventHandler::on_connect(get_client_address());
        std::ostringstream out;
        out << GREEN << "You have successfully joined" << RESET;
        send(out.str());
    };

    on_disconnect = [this]() {
        EventHandler::on_disconnect(get_client_address());
    };

    connect();

    send("Please enter your username");
    on_read = [this](const std::string& username) {
        try {
            authorize_user(username);
            std::ostringstream guide;
            guide << GREEN << "You are successfully authorized\n" << RESET;
            guide << YELLOW << "Available commands:\n";
            guide << "-> create \"title\" \"description\" \"date\" [usernames of collaborators ...]\n";
            guide << "-> list" << RESET;
            send(guide.str());
            display_commands();
        } catch (const InvalidUsernameException& e) {
            send(e.what(), MessageType::EXCEPTION);
        }
    };
}

User Session::get_user() const {
    return user;
}

void Session::display_commands() {
    send("Enter a command");
    on_read = [this](const std::string& command_line) {
        auto self = shared_from_this();
        CommandHandler command_handler(user, self);
        try {
            command_handler.execute(command_line);
        } catch (const InvalidCommandException& e) {
            send(e.what(), MessageType::EXCEPTION);
        }
        display_commands();
    };
}
