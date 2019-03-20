open JustgageReasonCookie;

let isConnected = true;
let saveUser = value => Cookie.setString("jsessionid", value);
let getUser = () => Cookie.getAsString("jsessionid");