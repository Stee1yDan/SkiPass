#pragma once

#include "view.hpp"

namespace SkiPass {
    class ExtendableTicket;

    class CLIView : public IView{
    public:

        ~CLIView() override;

        void show_balance(std::shared_ptr<ExtendableTicket> ticket) override;

        void show_ticket_info(TicketService::TicketInfo ticket_info) override;

        void show_message(const std::string &message) override;

        void show_storage_unit(std::shared_ptr<StorageUnit> unit) override;

        void show_error(const std::string &error) override;

        void show_all_storage_units(std::shared_ptr<IStorageUnitRepository> repository) override;

        void show_extension_prices(std::unordered_map<AbstractTicket::TicketType, unsigned> map) override;

        void show_ticket_created(std::shared_ptr<AbstractTicket> ticket) override;

        void show_all_tickets(std::shared_ptr<ITicketRepository> repository) override;
    };

}
