#include <vector>
#include <assert.h>
#include "db_fun.h"
#include "exchange_factory.h"
#include "iexchange_profile.h"


std::vector<Exchange_Factory::func_loader>& Exchange_Factory::get_loadlist()
{
  static std::vector<Exchange_Factory::func_loader> list;
  return list;
}

bool Exchange_Factory::add_loader(Exchange_Factory::func_loader loader)
{
  assert(loader);
  get_loadlist().push_back(loader);

  return true;
}

ExchangeCollection Exchange_Factory::register_exchanges(Parameters &params)
{
  ExchangeCollection exchanges;
  auto loadlist = get_loadlist();
  for(auto it = begin(loadlist); it != end(loadlist); ++it)
  {
    auto next = (*it)(params);
    if(next) exchanges.push_back(std::unique_ptr<IExchange_Profile> {next});
  }
  if(params.useDatabase)
    for(auto it = begin(exchanges); it != end(exchanges); ++it)
      createTable((*it)->name(), params);

  return exchanges;
}
