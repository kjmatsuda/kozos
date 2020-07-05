#ifndef D_kozos_unit_testBuildTime_H
#define D_kozos_unit_testBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  kozos_unit_testBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class kozos_unit_testBuildTime
  {
  public:
    explicit kozos_unit_testBuildTime();
    virtual ~kozos_unit_testBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    kozos_unit_testBuildTime(const kozos_unit_testBuildTime&);
    kozos_unit_testBuildTime& operator=(const kozos_unit_testBuildTime&);

  };

#endif  // D_kozos_unit_testBuildTime_H
