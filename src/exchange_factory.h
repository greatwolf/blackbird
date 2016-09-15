#ifndef EXCHANGE_FACTORY_H
#define EXCHANGE_FACTORY_H
#include <vector>
#include <memory>


class Parameters;
class IExchange_Profile;

using ExchangeCollection = std::vector< std::unique_ptr<IExchange_Profile> >;
class Exchange_Factory
{
  typedef IExchange_Profile* (*func_loader)(Parameters &params);
  static std::vector<Exchange_Factory::func_loader>& get_loadlist();

public:
  static bool add_loader(func_loader);
  static ExchangeCollection register_exchanges(Parameters &params);
};

#endif
