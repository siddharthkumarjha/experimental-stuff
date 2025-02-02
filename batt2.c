#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_battery_event(DBusMessage *msg)
{
    if (!msg)
        return;

    const char *member = dbus_message_get_member(msg);
    if (member && strcmp(member, "PropertiesChanged") == 0)
    {
        printf("Battery status changed!\n");

        DBusMessageIter args;
        if (dbus_message_iter_init(msg, &args))
        {
            char *interface_name;
            dbus_message_iter_get_basic(&args, &interface_name);
            if (interface_name &&
                strcmp(interface_name, "org.freedesktop.UPower.Device") == 0)
            {
                printf("Battery properties updated.\n");
            }
        }
    }
}

int main()
{
    DBusConnection *conn;
    DBusError err;
    dbus_error_init(&err);

    // Connect to DBus system bus
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
    if (!conn)
    {
        fprintf(stderr, "Failed to connect to DBus: %s\n", err.message);
        dbus_error_free(&err);
        return EXIT_FAILURE;
    }

    // Add match rule to listen for battery events
    dbus_bus_add_match(conn,
                       "type='signal',interface='org.freedesktop.DBus."
                       "Properties',member='PropertiesChanged'",
                       &err);
    dbus_connection_flush(conn);
    if (dbus_error_is_set(&err))
    {
        fprintf(stderr, "Match rule error: %s\n", err.message);
        dbus_error_free(&err);
        return EXIT_FAILURE;
    }

    printf("Listening for battery status changes...\n");

    while (1)
    {
        dbus_connection_read_write(conn, 1000);
        DBusMessage *msg = dbus_connection_pop_message(conn);
        if (msg)
        {
            handle_battery_event(msg);
            dbus_message_unref(msg);
        }
    }

    return EXIT_SUCCESS;
}
