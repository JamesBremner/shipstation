#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include <propertygrid.h>
#include <inputbox.h>
#include "cStarterGUI.h"
#include "shipChooser.h"

cShipChooser theShipChooser;

cGUI::cGUI()
    : cStarterGUI(
          "ShipChooser",
          {50, 50, 1000, 600}),
      lbCarriers(wex::maker::make<wex::label>(fm)),
      plPackage(wex::maker::make<wex::panel>(fm)),
      bnBatch(wex::maker::make<wex::button>(plPackage)),
      gpPackage(wex::maker::make<wex::groupbox>(plPackage)),
      lbWeight(wex::maker::make<wex::label>(plPackage)),
      edWeight(wex::maker::make<wex::editbox>(plPackage)),
      lbLength(wex::maker::make<wex::label>(plPackage)),
      edLength(wex::maker::make<wex::editbox>(plPackage)),
      lbWidth(wex::maker::make<wex::label>(plPackage)),
      edWidth(wex::maker::make<wex::editbox>(plPackage)),
      lbHeight(wex::maker::make<wex::label>(plPackage)),
      edHeight(wex::maker::make<wex::editbox>(plPackage)),
      lbSrc(wex::maker::make<wex::label>(plPackage)),
      edSrc(wex::maker::make<wex::editbox>(plPackage)),
      lbDst(wex::maker::make<wex::label>(plPackage)),
      edDst(wex::maker::make<wex::editbox>(plPackage)),
      rbCommercial(wex::maker::make<wex::radiobutton>(plPackage)),
      rbResidential(wex::maker::make<wex::radiobutton>(plPackage)),

      plCarrier(wex::maker::make<wex::panel>(fm)),
      gpCarrier(wex::maker::make<wex::groupbox>(plCarrier)),

      bnAuthorization(wex::maker::make<wex::button>(plCarrier)),
      bnCarriers(wex::maker::make<wex::button>(plCarrier)),
      pgCarrier(wex::maker::make<wex::propertyGrid>(plCarrier)),

      plChoice(wex::maker::make<wex::panel>(fm)),
      gpChoice(wex::maker::make<wex::groupbox>(plChoice)),
      bnChoose(wex::maker::make<wex::button>(plChoice)),
      lbChoice(wex::maker::make<wex::label>(plChoice)),
      edCost(wex::maker::make<wex::editbox>(plChoice)),
      edTime(wex::maker::make<wex::editbox>(plChoice)),

      plLogic(wex::maker::make<wex::panel>(fm)),
      gpLogic(wex::maker::make<wex::groupbox>(plLogic)),
      lbLogic(wex::maker::make<wex::label>(plLogic))

{

    constructPackagePanel(10, 20);
    constructCarrierPanel(250, 20);
    constructChoicePanel(500, 20);
    constructLogicPanel(750, 20);

    show();
    run();
}
void cGUI::constructPackagePanel(int x, int y)
{
    plPackage.move(x, y, 200, 500);
    gpPackage.move({10, 10, 190, 490});
    gpPackage.text("Package");

    bnBatch.move(50, 50, 70, 30);
    bnBatch.text("Batch");

    y = 90;
    int lbw = 80;
    int edx = lbw + 30;
    lbWeight.move(20, y, lbw, 30);
    lbWeight.text("Weight");
    edWeight.move(edx, y, 50, 30);
    edWeight.text("");

    y += 50;
    lbLength.move(20, y, lbw, 30);
    lbLength.text("Length");
    edLength.move(edx, y, 50, 30);
    edLength.text("");

    y += 50;
    lbWidth.move(20, y, lbw, 30);
    lbWidth.text("Width");
    edWidth.move(edx, y, 50, 30);
    edWidth.text("");

    y += 50;
    lbHeight.move(20, y, lbw, 30);
    lbHeight.text("Height");
    edHeight.move(edx, y, 50, 30);
    edHeight.text("");

    y += 50;
    lbSrc.move(20, y, lbw, 30);
    lbSrc.text("Source ZIP");
    edSrc.move(edx, y, 50, 30);
    edSrc.text("");

    y += 50;
    lbDst.move(20, y, lbw, 30);
    lbDst.text("Dest ZIP");
    edDst.move(edx, y, 50, 30);
    edDst.text("");

    y += 50;
    rbCommercial.move(20, y, 120, 30);
    rbCommercial.text("Commercial");
    y += 40;
    rbResidential.move(20, y, 120, 20);
    rbResidential.text("Residential");
}
void cGUI::constructCarrierPanel(int x, int y)
{
    vCarrier.clear();
    vCarrier.emplace_back("FedEX", "fedex",
                          "FedEx Ground®", "fedex_ground");
    vCarrier.emplace_back("FedEX", "fedex",
                          "FedEx Home Delivery®", "fedex_home_delivery");
    vCarrier.emplace_back("FedEX", "fedex",
                          "FedEx 2Day® A.M", "fedex_2day_am");

    plCarrier.move(x, y, 200, 500);
    gpCarrier.move({10, 10, 190, 490});
    gpCarrier.text("Carriers");

    y = 40;
    bnAuthorization.move(50, y, 100, 30);
    bnAuthorization.text("Authorization");
    bnAuthorization.events().click(
        [this]
        {
            Authorization();
        });

    y += 40;
    bnCarriers.move(50, y, 70, 30);
    bnCarriers.text("Update");
    bnCarriers.events().click(
        [this]
        {
            CarrierUpdate();
        });

    y += 50;
    pgCarrier.move({20, y, 170, 300});
    pgCarrier.labelWidth(120);
    pgCarrier.text("Service         Weight");
    auto curCarrier = vCarrier[0].myCarrierName;
    pgCarrier.category(curCarrier);
    for (auto &c : vCarrier)
    {
        if (c.myCarrierName != curCarrier)
        {
            curCarrier = c.myCarrierName;
            pgCarrier.category(curCarrier);
        }
        pgCarrier.string(c.text(), "1");
    }
}

void cGUI::constructChoicePanel(int x, int y)
{
    plChoice.move(x, y, 200, 400);
    gpChoice.move({10, 10, 190, 390});
    gpChoice.text("Choice");

    y = 50;
    bnChoose.move(50, y, 70, 30);
    bnChoose.text("CHOOSE");
    bnChoose.events().click(
        [this]
        {
            choose();
        });

    y += 50;
    lbChoice.move(20, y, 100, 200);
    lbChoice.text("Carrier: UPS \n\n\nCost: 20 \n\n\nTime: 2");
    y += 50;
    edCost.move(120, y, 70, 30);
    edCost.text(" 1");
    y += 50;
    edTime.move(120, y, 70, 30);
    edTime.text(" 1");
}
void cGUI::constructLogicPanel(int x, int y)
{
    plLogic.move(x, y, 200, 400);
    gpLogic.move({10, 10, 190, 390});
    gpLogic.text("Logic");
    lbLogic.move(20, 60, 170, 300);
    lbLogic.text("Maximize:\n\n"
                 "Carrier x Carrier Weight\n"
                 " - Cost x Cost Weight\n"
                 " - Time x Time Weight");
}

static std::string exec(const std::string &cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    // std::string cmd2 = cmd + " 2>&1";
    std::string cmd2 = cmd;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd2.c_str(), "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

void cGUI::choose()
{
    cPackage package;
    package.myWeight = atof(edWeight.text().c_str());

    for (auto &C : vCarrier)
    {
        float cost = C.cost(package);
    }
}

void cGUI::Authorization()
{
    wex::inputbox ib;
    ib.text("ShipStation Authorization");
    ib.gridWidth(500);
    ib.labelWidth(200);
    ib.add("User Name","");
    ib.add("Password","");
    ib.showModal();
    theShipChooser.Authorization =
        ib.value("User Name") + ":" + ib.value("Password");
}

void cGUI::CarrierUpdate()
{
    std::string cmd = 
        "curl -v -u " +
        theShipChooser.Authorization +
        " ssapi.shipstation.com/carriers";

    auto ret = exec(cmd);
    if( ret == "401 Unauthorized") {
        wex::msgbox("Authorization failed");
    }
}

cCarrier::cCarrier(
    const std::string &Carriername,
    const std::string &Carriercode,
    const std::string &Servicename,
    const std::string &Servicecode)
    : myCarrierName(Carriername),
      myCarrierCode(Carriercode),
      myServiceName(Servicename),
      myServiceCode(Servicecode),
      myFactorWeight(1)
{
}

std::string cCarrier::text() const
{
    auto ret = myServiceName;
    // int p = ret.find( myCarrierName );
    // if( p == 0 )
    ret = ret.substr(myCarrierName.length() + 1);
    int p = ret.find("®");
    if (p != -1)
        ret = ret.substr(0, p) + ret.substr(p + 2);
    return ret;
}

float cCarrier::cost(const cPackage &package)
{
    return 1;
}

std::string cCarrier::reqRateText()
{
    // https://www.shipstation.com/docs/api/shipments/get-rates/

    std::stringstream ss;
    ss << "POST /shipments/getrates HTTP/1.1\n"
          "Host: ssapi.shipstation.com\n"
          "Authorization:";
    ss << theShipChooser.Authorization + "\n";
    ss << "Content-Type: application/json\n"
          "{\n"
          "\"carrierCode\":" +
              myCarrierCode + ",\n";
    "";
    return ss.str();
}

main()
{
    cGUI theGUI;
    return 0;
}
