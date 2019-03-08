let styleInput = ReactDOMRe.Style.make(~paddingLeft="20px");

let url_dev: string = "http://localhost:8080/";

type state = {
  idFormation: string,
  name: string,
  description: string,
  admLevel: string,
  diplomaLevel: string,
  expertise: string,
  partTime: string,
  logoPath: string,
  link: string,
  duration: string,
  schoolName: string,
  schoolDescription: string,
  schoolPostalCode: string,
  schoolCity: string,
  lowestScore: int,
  highestScore: int,
  averageScore: float,
  error: string,
};

type action =
  | Nothing
  | Loading
  | Error(string)
  | Loaded(state);

let getTraining = state => {
  let payload = Js.Dict.empty();

  Js.Promise.(
    Fetch.fetchWithInit(
      // url_dev ++ "/training/" ++ state.idFormation,
      "./training.json",
      Fetch.RequestInit.make(
        ~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> DecodeTraining.decodeResponse
         |> (training => training) 
         |> resolve
       )
  );
};

let component = ReasonReact.reducerComponent("consultationFormation");

let make = _children => {
  ...component,
  initialState: () => {
      idFormation: "",
      name: "",
      description: "",
      admLevel: "",
      diplomaLevel: "",
      expertise: "",
      partTime: "",
      logoPath: "",
      link: "",
      duration: "",
      schoolName: "",
      schoolDescription: "",
      schoolPostalCode: "",
      schoolCity: "",
      lowestScore: 0,
      highestScore: 0,
      averageScore: 0.0,
      error: ""
  },
  reducer: (action, state) =>
    switch (action) {
    | Nothing => ReasonReact.NoUpdate
    | Loading =>
      ReasonReact.UpdateWithSideEffects(
        state,
        self =>
          Js.Promise.(
            getTraining(state)
            |> then_(result => resolve(self.send(Loaded(result))))
            |> catch(_err =>
                 Js.Promise.resolve(
                   self.send(Error("Erreur lors du chargement JSON")),
                 )
               )
            |> ignore
          ),
      );
    | Error(string) => ReasonReact.NoUpdate
    | Loaded(result) =>
      ReasonReact.Update({
        idFormation: result.idFormation,
        name: result.name,
        description: result.description,
        admLevel: result.admLevel,
        diplomaLevel: result.diplomaLevel,
        expertise: result.expertise,
        partTime: result.partTime,
        logoPath: result.logoPath,
        link: result.link,
        duration: result.duration,
        schoolName: result.schoolName,
        schoolDescription: result.schoolDescription,
        schoolPostalCode: result.schoolPostalCode,
        schoolCity: result.schoolCity,
        lowestScore: result.lowestScore,
        highestScore: result.highestScore,
        averageScore: result.averageScore,
        error: result.error,
      })
    },
  didMount: self => self.send(Loading),
  render: _self =>
    <div className="card align-middle mx-auto w-50 p-3 text-center">
      <div className="card-header">
        {ReasonReact.string("Consultation d'une formation")}
      </div>
      <div className="card-body">
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.name}
            placeholder="Nom de la formation"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.description}
            placeholder="Description de la formation"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.expertise}
            placeholder="Niveau d'expertise"
          />
        </div>
        <div className="input-group mb-3">
          <div className="input-group-prepend">
            <span className="input-group-text" id="">
              {ReasonReact.string("Alternance :")}
            </span>
          </div>
          <select className="form-control" id="pet-select">
            <option value="">
              {ReasonReact.string("Choix d'une option")}
            </option>
            <option value={_self.state.partTime}>
              {ReasonReact.string("Oui")}
            </option>
            <option value={_self.state.partTime}>
              {ReasonReact.string("Non")}
            </option>
          </select>
        </div>
        <div className="input-group mb-3">
          <div className="input-group-prepend">
            <span className="input-group-text" id="">
              {ReasonReact.string("Photo de la formation :")}
            </span>
          </div>
          <input
            className="styleInput"
            type_="file"
            value={_self.state.logoPath}
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.link}
            placeholder="lien du site de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.duration}
            placeholder="Durée de la formation"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolName}
            placeholder="Nom de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolDescription}
            placeholder="Description de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolPostalCode}
            placeholder="Code postale de la ville de l'école"
          />
        </div>
        <div className="input-group mb-3">
          <input
            className="form-control"
            type_="text"
            value={_self.state.schoolCity}
            placeholder="Nom de la ville de l'école"
          />
        </div>
      </div>
      <label> {ReasonReact.string(_self.state.name)} </label>
      <label> {ReasonReact.string(_self.state.description)} </label>
      <label> {ReasonReact.string(_self.state.partTime)} </label>
      <label> {ReasonReact.string(_self.state.error)} </label>
    </div>,
};
