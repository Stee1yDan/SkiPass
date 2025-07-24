
#include "abstract_ticket.hpp"
#include "abstract_ticket_repository.hpp"

namespace SkiPass {
 class TourniquetService {
   public:
     enum class pass_operation_status {
         success,
         ticket_expired,
         no_passes_left,
         wrong_tourniquet,
         no_such_ticket_found,
         operation_declined
     };

     explicit TourniquetService(const std::shared_ptr<ITicketRepository> &ticket_repository)
         : ticket_repository_(ticket_repository) {
     }

     ~TourniquetService() = default;

     [[nodiscard]] pass_operation_status pass_through_tourniquet(AbstractTicket::ticket_id_t id, unsigned tourniquet_id) const;
     [[nodiscard]] pass_operation_status can_pass_through_tourniquet(AbstractTicket::ticket_id_t id, unsigned tourniquet_id) const;


     TourniquetService & operator=(const TourniquetService &other) {
         if (this == &other)
             return *this;
         return *this;
     }

     TourniquetService & operator=(TourniquetService &&other) noexcept {
         if (this == &other)
             return *this;
         return *this;
     }

     private:
     std::shared_ptr<ITicketRepository> ticket_repository_;
 };
}
