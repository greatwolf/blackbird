#ifndef IEXCHANGE_PROFILE_H
#define IEXCHANGE_PROFILE_H
#include <string>


struct Parameters;

class IExchange_Profile
{
public:
  virtual double getQuote(bool isBid) = 0;
  virtual double getAvail(const std::string &currency) = 0;
  virtual int    sendLongOrder(const std::string &direction, double quantity, double price) = 0;
  virtual int    sendShortOrder(const std::string &direction, double quantity, double price) = 0;
  virtual bool   isOrderComplete(int orderId) = 0;
  virtual double getActivePos() = 0;
  virtual double getLimitPrice(double volume, bool isBid) = 0;

  virtual const char* name()          const = 0;
  virtual bool        canShort()      const = 0;
  virtual bool        isImplemented() const = 0;
  virtual double      getFees()       const = 0;
};

#endif
