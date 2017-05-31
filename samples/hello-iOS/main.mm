#include <UIKit/UIKit.h>
#include "AppDelegate.h"

int main(int argc, char* argv[])
{
    @autoreleasepool
    {
        int returnValue;
        @try
        {
            returnValue = UIApplicationMain(argc, argv, nil,
                                            NSStringFromClass([AppDelegate class]));
        }
        @catch (NSException* exception)
        {
            //LogError(@"Uncaught exception: %@, %@", [exception description],
              //       [exception callStackSymbols]);
            @throw exception;
        }
        return returnValue;
    }
}
