#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// Using a direct call will give syntax issues while this doesn't

// Why does it work work with a double defined and not a single define we will never know...
#define XENV(x) #x
#define ENV(x) XENV(x)
// ...but it works

#endif