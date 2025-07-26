#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>

namespace SkiPass {
    class AbstractTicket {
    public:

    enum class TicketType {
        UNLIMITED,
        TEMPORARY,
        LIMITED,
        SERVICE};

    using gender = std::string;
    using extension_unit_t = long long;
    using balance_unit_t = std::string;
    using ticket_id_t = unsigned int;

    AbstractTicket(ticket_id_t id,std::string full_name, unsigned age, gender gender, TicketType ticket_type)
        : ticket_id_t_(id),
          full_name_(std::move(full_name)),
          age_(age),
          gender_(std::move(gender)),
          ticket_type_(ticket_type){
    }

    virtual bool pass(unsigned tourniquet_id) = 0;
    virtual bool can_pass(unsigned tourniquet_id) = 0;
    [[nodiscard]] virtual std::shared_ptr<AbstractTicket> clone() const = 0;

    static bool tourniquet_exists(unsigned tourniquet_id);
    static bool is_service_tourniquet(unsigned tourniquet_id);

    [[nodiscard]] ticket_id_t get_id() const;

    [[nodiscard]] ticket_id_t set_id(AbstractTicket::ticket_id_t id);

    [[nodiscard]] std::string get_full_name() const;

    [[nodiscard]] unsigned get_age() const;

    [[nodiscard]] gender get_gender() const;

    [[nodiscard]] TicketType get_ticket_type() const;

    static std::string ticket_type_to_string(AbstractTicket::TicketType type);

    virtual ~AbstractTicket() = default;

    protected:

    ticket_id_t ticket_id_t_ = 0;
    std::string full_name_;
    unsigned int age_ = 0;
    gender gender_;
    TicketType ticket_type_;
    static const std::unordered_map<unsigned, bool> service_tourniquet_registry;
    };
    std::ostream& operator<<(std::ostream& os, AbstractTicket::TicketType ticket);

}