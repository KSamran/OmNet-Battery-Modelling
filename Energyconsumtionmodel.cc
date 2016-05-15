///////////////////////////////////////////////////////
///////////////////Khawaja Samran/////////////////////
///////////////Matriculation Number#29811028//////////
//////////////////Department: COMNETS///////////////
//////////////////University of Bremen/////////////
//////////////////////////////////////////////////
#include <string.h>
#include <omnetpp.h>


class Battrey_Model: public cSimpleModule
{
private:
    simtime_t random_charging_time;//Parameter for charging of the battery for random amount of tomw until reaches 100%
    int random_selection;//Parameter for random decision for charging
    simtime_t delay;// Inter sending delay
    double present_time=0,old_time=0,inter_arrival_time=0;//Variables to find the inter_Arrival_Time
    double battery_level_sender,battery_level_receiver;
  protected:

    virtual void initialize();// Initialize is called at the beginning of the simulation.
    virtual void handleMessage(cMessage *msg);//Use to handle the flow of the message in the network,
                                              //whenever a message arrives at the module
    virtual void recharge_sender();
    virtual void recharge_receiver();
};

Define_Module(Battrey_Model);

void Battrey_Model::initialize()
{
    battery_level_sender=100;//Initial percentage of Battery level for Sender
    battery_level_receiver=100;//Initial percentage of Battery level for Receiver
    EV<<"Battery Level of Sender= "<<battery_level_sender<<"%"<<endl;
    EV<<"Battery Level of Receiver= "<<battery_level_receiver<<"%"<<endl;
    if (strcmp("sender", getName()) == 0)//If module is sender then send massage
    {
        cMessage *event = new cMessage("I am sender");// Create and Send first message on gate "out"
        scheduleAt(0,event);//scheduleAt() function specifies when massage should be delivered
    }
}

void Battrey_Model::handleMessage(cMessage *event)
{
    delay=par("delayTime");
    if (event->isSelfMessage())//isSelfmessage() is used in handling own message ONLY!!
    {
        if ( battery_level_sender > 10)//if battery level is greater then 10; it does not shut down the itself
        {
            random_selection=rand()% 10+1;
            if (random_selection == 7)//random decision for charging of the battery.
            {
                EV<<"Charger is connected to the Sender_battery"<<endl;
                recharge_sender();
                EV<<"Battery Level of Sender= "<<battery_level_sender<<"%"<<endl;
                cMessage *msg2 = new cMessage("senderMsg");
                send(msg2, "out");
                scheduleAt(simTime()+delay,event);//Next message is scheduled at random time (simulation time plus delay )

            }
            else
            {
                EV<<"Charger is not connected to the Sender_battery"<<endl;
                battery_level_sender=battery_level_sender-0.8;
                EV<<"Battery Level of Sender= "<<battery_level_sender<<"%"<<endl;
                cMessage *msg2 = new cMessage("senderMsg");
                send(msg2, "out");
                battery_level_sender=battery_level_sender-(0.0013888889*delay.dbl());//battery is charged 10% per hour in idle mode
                scheduleAt(simTime()+delay,event);//Next message is scheduled at random time (simulation time plus delay )

            }
        }
        else//if battery level is less then 10; shut down the itself
        {
            EV <<"Sender Is Shut Down; Recharges it"<<endl;
            random_selection=rand()% 10+1;//random decision for charging of the battery in shut down mode
            if (random_selection == 7)//random decision for charging of the battery.
            {
                EV<<"Charger is connected to the Sender_battery"<<endl;
                battery_level_sender=battery_level_sender+6;
                recharge_sender();
                EV<<"Battery Level of Sender= "<<battery_level_sender<<"%"<<endl;
                scheduleAt(simTime()+delay,event);

            }
            else

            scheduleAt(simTime()+delay,event);
        }

}
    else// We are at the receiver
    {

        present_time=simTime().dbl();//Simulation time at the receiver
        inter_arrival_time=present_time-old_time;//we want to find Inter_arrival_Time
        battery_level_receiver=battery_level_receiver-(0.0013888889*inter_arrival_time );//battery is charged 10% per hour in idle mode
        old_time=present_time;//Shows time when the last message was arrived
       if ( battery_level_receiver > 10)//if battery level is greater then 10; it does not shut down the itself
            {
            random_selection=rand()% 10+1;
              if (random_selection == 7)//random decision for charging of the battery.
                {
                  EV<<"Charger is connected to the Receiver_battery"<<endl;
                  delete event;
                  recharge_receiver();
                  EV<<"Battery Level of Receiver= "<<battery_level_receiver<<"%"<<endl;


                }
              else
              {
                  EV<<"Charger is not connected to the Receiver_battery"<<endl;
                  delete event;
                  battery_level_receiver=battery_level_receiver-0.4;
                  EV<<"Battery Level of Receiver= "<<battery_level_receiver<<"%"<<endl;

              }
            }
        else//if battery level is less then 10; shut down  itself
        {
            EV <<"Receiver Is Shut Down, Recharges it"<<endl;
            random_selection=rand()% 10+1;//random decision for charging of the battery in shut down mode
             if (random_selection == 7)//random decision for charging of the battery.
             {
                 EV<<"Charger is connected to the Receiver_battery"<<endl;
                 battery_level_receiver=battery_level_receiver+6;
                 EV<<"Battery Level of Receiver= "<<battery_level_receiver<<"%"<<endl;


             }
        }

    }

}

void Battrey_Model::recharge_sender()
{
    random_charging_time=par("charging_time");// time for random charging
    EV<<"Sender is charged for = "<<random_charging_time/60<<" Minutes "<<endl;
    delay=delay+random_charging_time;
    battery_level_sender=battery_level_sender+(0.00833334*random_charging_time.dbl());//battery is charged 30% per hour

    if ( battery_level_sender < 100)//keeps battery level maximum to 100%
    {
        battery_level_sender=battery_level_sender;
    }
    else
        battery_level_sender=100;

}
void Battrey_Model::recharge_receiver()
{
    random_charging_time=par("charging_time");
    EV<<"Receiver is charged for = "<<random_charging_time/60<<" Minutes "<<endl;
    delay=delay+random_charging_time;
    battery_level_receiver=battery_level_receiver+(0.00833334*random_charging_time.dbl());//battery is charged 30% per hour
    if ( battery_level_receiver < 100)//keeps battery level maximum to 100%
    {
        battery_level_receiver=battery_level_receiver;
    }
    else
        battery_level_receiver=100;

}

