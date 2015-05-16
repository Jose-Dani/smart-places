package controllers;

import play.*;
import play.mvc.*;

import views.html.*;

public class Application extends Controller {

    public static Result index() {
        response().setContentType("text/plain");

		return ok("Hola ESP8266!!!");
    }

}
