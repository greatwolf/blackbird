#ifndef MAKE_EXCHANGE_H
#define MAKE_EXCHANGE_H
#include "parameters.h"
#include "iexchange_profile.h"


template <typename T, typename T_TRAITS>
class Exchange_Wrap : public IExchange_Profile
{
  Parameters &params;
  T exchangeAPI;

public:
  Exchange_Wrap(T &&exchangeAPI_, Parameters &params_)
    : params(params_), exchangeAPI( std::move(exchangeAPI_) )
    {}
  double getQuote(bool isBid) { return exchangeAPI.getQuote(params, isBid); }
  double getAvail(const std::string &currency)
  {
    return exchangeAPI.getAvail(params, currency);
  }
  int    sendLongOrder(const std::string &direction, double quantity, double price)
  {
    return exchangeAPI.sendLongOrder(params, direction, quantity, price);
  }
  int    sendShortOrder(const std::string &direction, double quantity, double price)
  {
    return exchangeAPI.sendShortOrder(params, direction, quantity, price);
  }
  bool   isOrderComplete(int orderId)
  {
    return exchangeAPI.isOrderComplete(params, orderId);
  }
  double getActivePos()
  {
    return exchangeAPI.getActivePos(params);
  }
  double getLimitPrice(double volume, bool isBid)
  {
    return exchangeAPI.getLimitPrice(params, volume, isBid);
  }

  const char* name()   const { return T_TRAITS::name; }
  bool canShort()      const { return T_TRAITS::shortable; }
  bool isImplemented() const { return T_TRAITS::implemented; }
  double getFees()     const { return T_TRAITS::fees(params); }
};

template <typename T, typename T_TRAITS>
IExchange_Profile* make_exchange(Parameters &params)
{
  if (!params.demoMode && T_TRAITS::apiKey(params).empty()) return nullptr;

  std::string apiKey    = T_TRAITS::apiKey(params),
              apiSecret = T_TRAITS::apiSecret(params);
  return new Exchange_Wrap<T, T_TRAITS>(T { apiKey, apiSecret }, params);
}

#endif
