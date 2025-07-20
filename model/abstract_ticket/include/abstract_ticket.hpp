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

    using gender_t = std::string;
    using extension_unit_t = long long;
    using balance_unit_t = std::string;
    using ticket_id_t = unsigned int;

    static const std::unordered_map<unsigned, bool> service_tourniquet_registry;

    AbstractTicket(ticket_id_t id,std::string full_name, unsigned age, gender_t gender, TicketType ticket_type)
        : id(id),
          full_name(std::move(full_name)),
          age(age),
          gender(std::move(gender)),
          ticket_type(ticket_type){
    }

    virtual bool pass(unsigned tourniquet_id) = 0;
    virtual bool can_pass(unsigned tourniquet_id) = 0;
    [[nodiscard]] virtual std::shared_ptr<AbstractTicket> clone() const = 0;

    static bool tourniquet_exists(unsigned tourniquet_id);
    static bool is_service_tourniquet(unsigned tourniquet_id);

    static std::string ticket_type_to_string(AbstractTicket::TicketType type);

    virtual ~AbstractTicket();

    ticket_id_t id{};
    std::string full_name;
    unsigned age{};
    gender_t gender;
    TicketType ticket_type;
    };
    std::ostream& operator<<(std::ostream& os, AbstractTicket::TicketType ticket);

}